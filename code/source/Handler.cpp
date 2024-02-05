/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-22 15:18:01
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-12-02 16:35:30
 * @FilePath: /Simple_geometric_expert_system/code/source/Handler.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "../include/Handler.h"
#include <fstream>
#include <ios>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/matx.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>


Handler::Handler(std::string source) {
    src = cv::imread(source);
    contours = getContours(this->src);
    if(!contours.empty()) contours.erase(contours.begin());
}

Handler::~Handler() {

}

float calculateLength(ContourLine l) {
    return std::sqrt(std::pow((l.p2.x - l.p1.x),2) + std::pow((l.p2.y - l.p1.y),2));
}

float calculateAngle(ContourLine l) {
    // 判断垂直情况
    if (l.p2.x == l.p1.x) {
        return 90.0;
    }
    return std::atan2(l.p2.y - l.p1.y, l.p2.x - l.p1.x) * 180.0 / M_PI;
}

float calculateInnerAngle(ContourLine l1, ContourLine l2) {
    cv::Point2f intersection = getMeetingPoint(l1, l2);
    if(intersection.x == -1 && intersection.y == -1) {
        return 361.0;     // 平行
    }
    else if(intersection.x == -2 && intersection.y == -2 ) {
        return 362.0;   // 不相交
    }
    else {
        cv::Point2f p1 = averagePoint(l1.p1, l1.p2);
        cv::Point2f p2 = averagePoint(l2.p1, l2.p2);
        Vector_ v1 = getVector(intersection, p1);
        Vector_ v2 = getVector(intersection, p2);
        int inner_product = getInnerProduct(v1,v2);
        float cos_theta = inner_product / (std::sqrt(getInnerProduct(v1, v1)) * std::sqrt(getInnerProduct(v2, v2)));

        return 
            std::acos(cos_theta) * 180.0 / M_PI;
    }
}

float getInnerProduct(Vector_ v1, Vector_ v2) {  // 向量内积
    return v1.x * v2.x + v1.y * v2.y;
}

std::vector<std::vector<cv::Point>> Handler::getContours(cv::Mat img) {
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    cv::Mat threshold;
    cv::threshold(gray, threshold, 127, 255, cv::THRESH_BINARY);
    std::vector<std::vector<cv::Point> > contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(threshold, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // contours
    for(int i=1; i<contours.size(); i++){
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contours[i], approx, 0.01 * cv::arcLength(contours[i], true), true);
        contours[i] = approx;
    }

    return contours;
}

// void Handler::getLines() {

// }


std::vector<ContourLine> Handler::generateLines(std::vector<cv::Point>  contour) {
    std::cout << contour.size() << std::endl;
    std::vector<ContourLine> contour_lines;
    for(int i=0; i<contour.size()-1; i++) {
        contour_lines.push_back(  ContourLine(contour[i], contour[i+1])  );
    }
    contour_lines.push_back( ContourLine(contour.back(), contour.front()) );

    return contour_lines;
}

void Handler::generateContour_dict() {
    for(int i=0; i<contours.size(); i++) {
        contours_dict.emplace_back(generateLines(this->contours[i]));
    }
}

bool closeEnough(cv::Point p1, cv::Point p2) {
    return (std::pow((p2.y - p1.y),2)+std::pow((p2.x-p1.x),2)) < close_threshold;
}

cv::Point2f averagePoint(cv::Point p1, cv::Point p2) {
    return cv::Point2f((float)(p1.x+p2.x)/2, (float)(p1.y+p2.y)/2);
}

Vector_ getVector(cv::Point p1, cv::Point p2) {
    return Vector_(p2.x-p1.x, p2.y-p1.y);
}

/* 判断锐角 */
bool isAcute(ContourLine l1, ContourLine l2) {
    float angle = calculateInnerAngle(l1, l2);
    if(angle < 90) {
        return true;
    }

    return false;
}

/* 判断钝角 */
bool isObtuse(ContourLine l1, ContourLine l2) {
    float angle = calculateInnerAngle(l1, l2);
    if(angle > 90 && angle < 360) return true;
    
    return false;
}

/* 是否封闭 */
bool isClosure(std::vector<ContourLine> lines) {
    bool flag = true;
    cv::Point2f intersection;
    for(int i=0; i<lines.size()-1; i++) {
        intersection = getMeetingPoint(lines[i], lines[i+1]);
        if(intersection.x == -1 && intersection.y == -1
            || (intersection.x == -2 && intersection.y == -2) 
        ) {
            // flag &= false;
            return false;
        }
        else {
            flag &= true;
        }
    }
    intersection = getMeetingPoint(lines[lines.size()-1], lines[0]);
    if( (intersection.x == -1 && intersection.y == -1)
        || (intersection.x == -2 && intersection.y == -2)
    ) {
        // flag &= false;
        return false;
    } 
    else {
        flag &= true;
    }

    return flag;
}


// 是否相交， 不相交返回 Point{-2,-2}  平行返回{-1, -1}
cv::Point2f getMeetingPoint(ContourLine l1, ContourLine l2) {    
    // 平行
    if((std::abs(l1.angle - l2.angle) <= 1) 
        || std::abs(l1.angle - l2.angle) <= 181 && std::abs(l1.angle - l2.angle) >= 179) {
        return cv::Point2f(-1,-1); 
    }
    double k1, k2;
    k1 = (double)(l1.p2.y - l1.p1.y) / (double)(l1.p2.x - l1.p1.x); //求出l1斜率
    k2 = (double)(l2.p2.y - l2.p1.y) / (double)(l2.p2.x - l2.p1.x); //求出l2斜率

    cv::Point2f crossPoint;
    crossPoint.x = (k1*l1.p1.x - l1.p1.y - k2*l2.p1.x + l2.p1.y) / (k1 - k2);
    crossPoint.y = k1*crossPoint.x + (l1.p1.y - k1*l1.p1.x);

    if(crossPoint.x < std::min(l1.p1.x, l1.p2.x) || crossPoint.x > std::max(l1.p1.x, l1.p2.x) ||
       crossPoint.x < std::min(l2.p1.x, l2.p2.x) || crossPoint.x > std::max(l2.p1.x, l2.p2.x) ||
       crossPoint.y < std::min(l1.p1.y, l1.p2.y) || crossPoint.y > std::max(l1.p1.y, l1.p2.y) ||
       crossPoint.y < std::min(l2.p1.y, l2.p2.y) || crossPoint.y > std::max(l2.p1.y, l2.p2.y)) {


        return cv::Point2f(-2,-2);
    }


    return crossPoint;
}

bool isLengthEqual(ContourLine l1, ContourLine l2) {
    return calculateLength(l1)-calculateLength(l2) < equal_threshold ? true : false;
}

bool isLengthEqual(std::vector<ContourLine> lines) {
    bool flag = true;
    for(int i = 0; i < lines.size()-1; i++) {
        flag &= isLengthEqual(lines[i], lines[i+1]);
    }
    return flag;
}

bool isParallel(ContourLine l1, ContourLine l2) {
    float angle = calculateInnerAngle(l1, l2);
    if(angle == 361.0 ) return true;
    
    return false;
}

bool isVertical(ContourLine l1, ContourLine l2) {
    float angle = calculateInnerAngle(l1, l2);
    if(std::abs(angle - 90) < vertical_threshold) return true;
    
    return false;
}

void factLinesClosureNumber(std::vector<Fact> &facts, std::vector<ContourLine> &lines) {
    switch (lines.size()) {
        case 3: 
            if(isClosure(lines)) 
                facts.push_back(Fact("3 closure lines", lines));   
            break;
        case 4: 
            if(isClosure(lines)) 
                facts.push_back(Fact("4 closure lines", lines));   
            break;
        case 5: 
            if(isClosure(lines)) 
                facts.push_back(Fact("5 closure lines", lines));   
            break;
        case 6: 
            if(isClosure(lines)) 
                facts.push_back(Fact("6 closure lines", lines));   
            break;
        default:
            facts.push_back(Fact("no closure lines", lines));
            break;
    }
}

void factLinesClosureEqual(std::vector<Fact> &facts, std::vector<ContourLine> &lines) {
    if(isLengthEqual(lines)) 
        facts.push_back(Fact("lines are all equal", lines));
}
void factLinesClosureParallel(std::vector<Fact> &facts) {
    int count = 0;
    std::vector<ContourLine> lines;
    std::vector<Fact> del;
    for(auto fact : facts) {
        if(fact.fact == "2 lines are parallel") {
            for(auto single : fact.about) {
                lines.push_back(single);
            }
            count++;
            del.push_back(fact);
        }
    }
    // 删除facts 中 与del相同的成员

    // for(std::vector<Fact>::iterator it = del.begin(); it != del.end(); it++){
    //     for(auto it2 = facts.begin(); it2 != facts.end(); it2++){
    //         if( *it == *it2) {
    //             facts.erase(it2);
    //         }
    //     }
    // }
    
    if(count) {
        facts.push_back(Fact(std::to_string(count)+" pairs of parallel lines", lines));
    }
}
void factAngleAcuteNumber(std::vector<Fact> &facts) {
    int count = 0;
    std::vector<ContourLine> lines;
    // std::vector<Fact> del;
    for(auto fact : facts) {
        if(fact.fact == "1 angle is acute angle") {
            for(auto single : fact.about) {
                lines.push_back(single);
            }
            count++;
            // del.push_back(fact);
        }
    }
    // // 删除facts 中 与del相同的成员
    // for(std::vector<Fact>::iterator it = del.begin(); it != del.end(); it++){
    //     for(auto it2 = facts.begin(); it2 != facts.end(); it2++){
    //         if( *it == *it2) {
    //             facts.erase(it2);
    //         }
    //     }
    // }
    
    if(count) {
        facts.push_back(Fact(std::to_string(count)+" angles are acute angle", lines));
    }
}
void factAngleRightNumber(std::vector<Fact> &facts) {
    int count = 0;
    std::vector<ContourLine> lines;
    for(auto fact : facts) {
        if(fact.fact == "1 angle is right angle") {
            for(auto single : fact.about) {
                lines.push_back(single);
            }
            count++;
        }
    }
    if (count) {
        facts.push_back(Fact(std::to_string(count)+" angles are right angle", lines));
    }
}
void factAboutAngle(std::vector<Fact> &facts, ContourLine l1, ContourLine l2) {
    if(isParallel(l1, l2)) {
        facts.push_back(Fact("2 lines are parallel",{l1,l2}));
    }
    else if(isVertical(l1, l2)) {
        facts.push_back(Fact("1 angle is right angle",{l1,l2}));
    }
    else if(isAcute(l1, l2)) {
        facts.push_back(Fact("1 angle is acute angle",{l1,l2}));
    }
    else if(isObtuse(l1, l2)) {
        facts.push_back(Fact("1 angle is obtuse angle",{l1,l2}));
    }
}
void factAboutlength(std::vector<Fact> &facts, ContourLine l1, ContourLine l2) {
    if(isLengthEqual(l1,l2)) {
        facts.push_back(Fact("2 lines are equal",{l1,l2}));
    }
}
std::pair<std::vector<Fact>,std::vector<Fact>> factGenerate(std::vector<ContourLine> lines) {
    std::vector<Fact> line_facts;
    std::vector<Fact> angle_facts;
    for(int i=0;i<lines.size()-1;i++) {
        for(int j=i+1;j<lines.size();j++) {
            factAboutlength(line_facts, lines[i], lines[j]);
            factAboutAngle(angle_facts, lines[i], lines[j]);   
        }
    }
    factLinesClosureNumber(line_facts, lines);
    factLinesClosureEqual(line_facts, lines);
    factLinesClosureParallel(angle_facts);
    factAngleAcuteNumber(angle_facts);
    factAngleRightNumber(angle_facts);

    return std::make_pair(line_facts,angle_facts);
}





/***************************************************************************************/
/**=======================================Fact=========================================*/
/***************************************************************************************/


Fact::Fact() {

}
Fact::Fact(std::string fact) : fact(fact) {

}
Fact::Fact(std::string fact, std::vector<ContourLine> about) : fact(fact), about(about){

}
Fact::~Fact() {

}

std::string Fact::toString() {
    std::string str = "";
    str += "<\n" + this->fact + "\n";
    for(auto const single : about) {
        str += "  " + single.toString() + "\n";
    }
    str += ">\n";
    return str;
}


bool Fact::operator == (Fact f) {
    bool flag = true;
    if (this->fact == f.fact) {
        for(int i=0; i<this->about.size();i++) {
            if(this->about[i] == f.about[i]){
                flag &= true;
            }
            else {
                return false;
            }
        }
    }

    return flag;
}


/***************************************************************************************/
/**=======================================ContourLine==================================*/
/***************************************************************************************/
ContourLine::ContourLine() {

}
ContourLine::ContourLine(cv::Point p1, cv::Point p2) : p1(p1), p2(p2){
    length = std::sqrt(std::pow((p2.x - p1.x),2) + std::pow((p2.y - p1.y),2));

    if (p1.x == p2.x) {
        angle = 90.0;
    }
    else {
        angle = std::atan2(p2.y - p1.y, p2.x - p1.x) * 180.0 / M_PI;
    }
}

ContourLine::~ContourLine() {

}

std::string ContourLine::toString() const{
    std::string str = "";
    str += "(" + std::to_string(p1.x) + "," + std::to_string(p1.y) + ") ---->" + "(" + std::to_string(p2.x) + "," + std::to_string(p2.y) + "): Length" + std::to_string(length) + ", Angle: " + std::to_string(angle);
    return str;
}

bool ContourLine::operator == (ContourLine c) {
    if(this->p1 == c.p1 && this->p2 == c.p2) {
        return true;
    }
    return false;
}


/***************************************************************************************/
/**=======================================ContourFact==================================*/
/***************************************************************************************/
ContourFact::ContourFact(int number, std::vector<Fact> line_facts, std::vector<Fact> angle_facts) : number(number), line_facts(line_facts), angle_facts(angle_facts){

}

ContourFact::~ContourFact() {

}

std::string ContourFact::toString() {
    std::string str;
    str += "--About Lines--" + std::to_string(number) + " lines\n";
    for(auto single : line_facts) {
        str += single.toString();
    }
    str += "--About Angles--\n";
    for(auto single : angle_facts) {
        str += single.toString();
    }
    str += "}\n";
    return str;
}


/***************************************************************************************/
/**=======================================FactGenerator==================================*/
/***************************************************************************************/
FactGenerator::FactGenerator(std::vector<std::vector<ContourLine>>  contours_dict) : contours_dict(contours_dict){

    file.open("../facts/facts.txt", std::ios::app);
    if(!file.is_open()) {
        std::cout << "FactGenerator open file error" << std::endl;
    }
}

FactGenerator::~FactGenerator() {
    if(file.is_open()) {
        file.close();
        std::cout << "file close" << std::endl;
    }
}

void FactGenerator::generateFact() {
    for(int i=0; i<contours_dict.size(); i++) {
        std::vector<ContourLine> lines = contours_dict[i];
        std::pair<std::vector<Fact>,std::vector<Fact>> line_angle_facts = factGenerate(lines);

        ContourFact cntfact = ContourFact(lines.size(), line_angle_facts.first, line_angle_facts.second);

        handled_facts["Contour" + std::to_string(i)] = (cntfact);

        file << "Contour #" << std::to_string(i) << "\n{\n";
        file << cntfact.toString();
    }
}