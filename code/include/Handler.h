/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-22 15:17:54
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-12-01 22:10:39
 * @FilePath: /Simple_geometric_expert_system/code/include/Handler.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __HANDLER_H__
#define __HANDLER_H__

#include <fstream>
#include <iostream>
#include <cmath>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <vector>


#define close_threshold  5      
#define equal_threshold  5
#define parallel_threshold  5
#define vertical_threshold  5


// struct Point {
//     float x;
//     float y;
// };

struct Line {
    cv::Point start;
    cv::Point end;
    float angle;

    Line(cv::Point start, cv::Point end) : start(start), end(end) {
        if (start.x == end.x) {
            angle =  90.0;
        }
        else {
            angle = std::atan2(end.y - start.y, end.x - start.x) * 180.0 / M_PI;
        }
    }

    bool operator == (Line l) {
        return (this->start == l.start && this->end == l.end && this->angle == l.angle);
    }
    bool operator != (Line l) {
        return !(this->start == l.start && this->end == l.end && this->angle == l.angle);
    }

    std::string toString() const {
        return "start: " + std::to_string(start.x) + "," + std::to_string(start.y) + " end: " + std::to_string(end.x) + "," + std::to_string(end.y) + " angle: " + std::to_string(angle);
    }
};

struct Vector_ {
    int x;
    int y;

    Vector_(int x, int y) : x(x), y(y) {}
};


/*************************************************************************************************/
/*********************************************Class Handler***************************************/
/*************************************************************************************************/
class Fact;
class ContourLine;
class Handler {
public:
    Handler(std::string source);
    ~Handler();



    std::vector<std::vector<cv::Point>> getContours(cv::Mat img);

    // void getLines();

    std::vector<ContourLine> generateLines(std::vector<cv::Point>  get_contours);

    void generateContour_dict();

public:
    cv::Mat src;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<ContourLine>>  contours_dict;
};


/*************************************************************************************************/
/*********************************************Class Fact***************************************/
/*************************************************************************************************/
class Fact {
public:
    Fact();
    Fact(std::string fact);
    Fact(std::string fact, std::vector<ContourLine> about);
    ~Fact();
    
    std::string toString();

    bool operator == (Fact f);

public:
    std::string fact;
    std::vector<ContourLine> about;

};


/*************************************************************************************************/
/*********************************************Class ContourLine***********************************/
/*************************************************************************************************/
class ContourLine {
public:
    ContourLine();
    ContourLine(cv::Point p1, cv::Point p2);
    ~ContourLine();

    std::string toString() const;
    
    bool operator == (ContourLine c);

public:
    cv::Point p1;
    cv::Point p2;
    float length;
    float angle;
};

/*************************************************************************************************/
/*********************************************Class ContourFact***********************************/
/*************************************************************************************************/
class ContourFact {
public:
    ContourFact() = default;
    ContourFact(int number, std::vector<Fact> line_facts, std::vector<Fact> angle_facts);
    ~ContourFact();

    std::string toString();


    // bool operator == (ContourFact c);

public:
    int number;
    std::vector<Fact> line_facts;
    std::vector<Fact> angle_facts;
};



/*************************************************************************************************/
/*********************************************Class FactGenerator*********************************/
/*************************************************************************************************/
class FactGenerator {
public:
    FactGenerator() = default;
    FactGenerator(std::vector<std::vector<ContourLine>>  contours_dict);
    ~FactGenerator();

    void generateFact();


public:
    std::vector<std::vector<ContourLine>>  contours_dict;
    std::map<std::string, ContourFact> handled_facts;
    std::ofstream file;
};




/*************************************************************************************************/
/*********************************************public Function*************************************/
/*************************************************************************************************/
bool closeEnough(cv::Point x1, cv::Point x2);
cv::Point2f averagePoint(cv::Point x1, cv::Point x2);
Vector_ getVector(cv::Point x1, cv::Point x2);
float getInnerProduct(Vector_ v1, Vector_ v2);  // 向量内积

float calculateLength(ContourLine l);
float calculateAngle(ContourLine l);
float calculateInnerAngle(ContourLine l1, ContourLine l2);

/* 判断锐角 */
bool isAcute(ContourLine l1, ContourLine l2);

/* 判断钝角 */
bool isObtuse(ContourLine l1, ContourLine l2);

/* 是否封闭 */
bool isClosure(std::vector<ContourLine> lines);

/* 获取交点 */
cv::Point2f getMeetingPoint(ContourLine l1, ContourLine l2);      

bool isLengthEqual(ContourLine l1, ContourLine l2);

bool isLengthEqual(std::vector<ContourLine> lines);

bool isParallel(ContourLine l1, ContourLine l2);

bool isVertical(ContourLine l1, ContourLine l2);
void factLinesClosureNumber(std::vector<Fact> &facts, std::vector<ContourLine> &lines);
void factLinesClosureEqual(std::vector<Fact> &facts, std::vector<ContourLine> &lines);
void factLinesClosureParallel(std::vector<Fact> &facts);
void factAngleAcuteNumber(std::vector<Fact> &facts);
void factAngleRightNumber(std::vector<Fact> &facts);
void factAboutAngle(std::vector<Fact> &facts, ContourLine l1, ContourLine l2);
void factAboutlength(std::vector<Fact> &facts, ContourLine l1, ContourLine l2);
std::pair<std::vector<Fact>,std::vector<Fact>> factGenerate(std::vector<ContourLine> lines);



#endif  //__HANDLER_H__