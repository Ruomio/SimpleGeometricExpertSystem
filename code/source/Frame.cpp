/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-26 16:11:01
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-12-02 17:32:28
 * @FilePath: /Simple_geometric_expert_system/code/source/Frame.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */


#include "../include/Frame.h"
#include <opencv2/core/types.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <qboxlayout.h>
#include <qstringliteral.h>
#include <qtreewidget.h>
#include <qtreewidgetitemiterator.h>
#include <string>

Frame::Frame(QWidget *parent) : QWidget(parent){
    InitWindow();
    InitConnect();
}

Frame::~Frame() {
    if(m_frame_widget) {
        delete m_frame_widget;
        m_frame_widget = nullptr;
    }
    if(m_rule_edit) {
        delete m_rule_edit;
        m_rule_edit = nullptr;
    }
    if(m_all_rules_widget) {
        delete m_all_rules_widget;
        m_all_rules_widget = nullptr;
    }
    if(m_all_facts_widget) {
        delete m_all_facts_widget;
        m_all_facts_widget = nullptr;
    }
}


void Frame::ShowWindow() {
    m_frame_widget->show();
}

void Frame::InitWindow() {

    m_frame_widget = new QWidget();
    m_frame_widget->setBaseSize(1000, 800);
    m_frame_widget->setStyleSheet("QWidget#frame_widget{background-color:#282828;}");
    m_frame_widget->setWindowTitle("Simple Geometric Expert System");

    m_layout = new QGridLayout(m_frame_widget);

    m_source_label = new QLabel("Source Image", m_frame_widget);
    m_detection_label = new QLabel("Detection Image", m_frame_widget);
    m_dection_result_label = new QLabel("Detection Result", m_frame_widget);
    m_matched_facts_label = new QLabel("Matched Facts", m_frame_widget);
    m_hit_rules_label = new QLabel("Hit Rules", m_frame_widget);
    m_label_shape = new QLabel("What's Shape do you want", m_frame_widget);

    m_scene_source = new QGraphicsScene(m_frame_widget);
    m_scene_detection = new QGraphicsScene(m_frame_widget);
    m_view_source = new QGraphicsView(m_scene_source, m_frame_widget);
    m_view_detection = new QGraphicsView(m_scene_detection, m_frame_widget);

    m_open_image = new QPushButton(QStringLiteral("Open Image"), m_frame_widget);
    m_open_rule_edit = new QPushButton(QStringLiteral("Open Rule Edit"), m_frame_widget);
    m_show_rules = new QPushButton(QStringLiteral("Show Rules"), m_frame_widget);
    m_show_facts = new QPushButton(QStringLiteral("Show Facts"), m_frame_widget);

    m_tree_widget = new QTreeWidget(m_frame_widget);
    m_tree_widget->setExpandsOnDoubleClick(false);
    m_tree_widget->setColumnCount(1);
    m_tree_widget->setHeaderLabel(QStringLiteral("Please double click a shape"));
    QTreeWidgetItem *all_shape = new QTreeWidgetItem(m_tree_widget);
    all_shape->setText(0, "All Shapes");
    QTreeWidgetItem *triangle_shape = new QTreeWidgetItem(all_shape);
    triangle_shape->setText(0, "Triangle");
    QTreeWidgetItem *acute_triangle_shape = new QTreeWidgetItem(triangle_shape);
    acute_triangle_shape->setText(0, "Acute Triangle");
    QTreeWidgetItem *right_triangle_shape = new QTreeWidgetItem(triangle_shape);
    right_triangle_shape->setText(0, "Right Triangle");
    QTreeWidgetItem *obtuse_triangle_shape = new QTreeWidgetItem(triangle_shape);
    obtuse_triangle_shape->setText(0, "Obtuse Triangle");
    QTreeWidgetItem *isosceles_triangle_shape = new QTreeWidgetItem(triangle_shape);
    isosceles_triangle_shape->setText(0, "Isosceles Triangle");
    QTreeWidgetItem *acute_isosceles_triangle_shape = new QTreeWidgetItem(isosceles_triangle_shape);
    acute_isosceles_triangle_shape->setText(0, "Acute and Isosceles Triangle");
    QTreeWidgetItem *right_isosceles_triangle_shape = new QTreeWidgetItem(isosceles_triangle_shape);
    right_isosceles_triangle_shape->setText(0, "Right and Isosceles Triangle");
    QTreeWidgetItem *obtuse_isosceles_triangle_shape = new QTreeWidgetItem(isosceles_triangle_shape);
    obtuse_isosceles_triangle_shape->setText(0, "Obtuse and Isosceles Triangle");
    QTreeWidgetItem *equilateral_triangle_shape = new QTreeWidgetItem(triangle_shape);
    equilateral_triangle_shape->setText(0, "Equilateral Triangle");


    QTreeWidgetItem *quadrilateral_shape = new QTreeWidgetItem(all_shape);
    quadrilateral_shape->setText(0, "Quadrilateral");
    QTreeWidgetItem *rhombus_shape = new QTreeWidgetItem(quadrilateral_shape);
    rhombus_shape->setText(0, "Rhombus");
    QTreeWidgetItem *parallelogram_shape = new QTreeWidgetItem(quadrilateral_shape);
    parallelogram_shape->setText(0, "Parallelogram");
    QTreeWidgetItem *rectangle_shape = new QTreeWidgetItem(parallelogram_shape);
    rectangle_shape->setText(0, "Rectangle");
    QTreeWidgetItem *square_shape = new QTreeWidgetItem(parallelogram_shape);
    square_shape->setText(0, "Square");
    QTreeWidgetItem *trapezium = new QTreeWidgetItem(quadrilateral_shape);
    trapezium->setText(0, "Trapezoid");
    QTreeWidgetItem *isosceles_trapezium_shape = new QTreeWidgetItem(trapezium);
    isosceles_trapezium_shape->setText(0, "Isosceles Trapezoid");
    QTreeWidgetItem *right_trapezium_shape = new QTreeWidgetItem(trapezium);
    right_trapezium_shape->setText(0, "Right Trapezoid");


    QTreeWidgetItem *pentagon_shape = new QTreeWidgetItem(all_shape);
    pentagon_shape->setText(0, "Pentagon");
    QTreeWidgetItem *regular_pentagon_shape = new QTreeWidgetItem(pentagon_shape);
    regular_pentagon_shape->setText(0, "Regular Pentagon");


    QTreeWidgetItem *hexagon_shape = new QTreeWidgetItem(all_shape);
    hexagon_shape->setText(0, "Hexagon");
    QTreeWidgetItem *regular_hexagon_shape = new QTreeWidgetItem(hexagon_shape);
    regular_hexagon_shape->setText(0, "Regular Hexagon");

    m_dection_result_text = new QPlainTextEdit(m_frame_widget);
    m_matched_facts_text = new QPlainTextEdit(m_frame_widget);
    m_hit_rules_text = new QPlainTextEdit(m_frame_widget);

    
    m_layout->addWidget(m_source_label,0,0,1,4);
    m_layout->addWidget(m_view_source, 1,0,8,4);
    m_layout->addWidget(m_detection_label, 0,4,1,4);
    m_layout->addWidget(m_view_detection, 1,4,8,4);
    m_layout->addWidget(m_open_image, 1,8,1,1);
    m_layout->addWidget(m_open_rule_edit,2,8,1,1);
    m_layout->addWidget(m_show_rules,3,8,1,1);
    m_layout->addWidget(m_show_facts,4,8,1,1);
    m_layout->addWidget(m_label_shape, 5,8,1,1);
    m_layout->addWidget(m_tree_widget, 6,8,3,1);
    m_layout->addWidget(m_dection_result_label,9,0,1,3);
    m_layout->addWidget(m_matched_facts_label,9,3,1,3);
    m_layout->addWidget(m_hit_rules_label,9,6,1,3);
    m_layout->addWidget(m_dection_result_text,10,0,3,3);
    m_layout->addWidget(m_matched_facts_text,10,3,3,3);
    m_layout->addWidget(m_hit_rules_text,10,6,3,3);

    m_layout->setColumnStretch(0,1);
    m_layout->setColumnStretch(4,1);
    m_layout->setColumnStretch(8,0);
}
void Frame::InitConnect() {
    connect(m_open_image, &QPushButton::clicked, this, &Frame::OpenSourceBtnSlot);
    connect(m_open_rule_edit, &QPushButton::clicked, this, &Frame::OpenRuleEditBtnSlot);
    connect(m_show_rules, &QPushButton::clicked, this, &Frame::ShowRulesBtnSlot);
    connect(m_show_facts, &QPushButton::clicked, this, &Frame::ShowFactsBtnSlot);
    connect(m_tree_widget, &QTreeWidget::itemDoubleClicked, this, &Frame::QTreeWidgetItemDoubleClickedSlot);
}

void Frame::OpenSourceBtnSlot() {
    if(!m_file_dialog) {
        m_file_dialog = new QFileDialog(this);
    }
    m_file_dialog->setWindowTitle(QStringLiteral("请选择图像"));
    m_file_dialog->setDirectory("../test_images");
    m_file_dialog->setNameFilter(QStringLiteral("Images(*.jpg *.png *.bmp)"));

    if(m_file_dialog->exec()) {
        image_path = m_file_dialog->selectedFiles()[0];
    }

    // std::cout << image_path.toStdString() << std::endl;
    m_scene_source->clear();
    m_scene_source->addPixmap(image_path);
    m_view_source->fitInView(m_scene_source->sceneRect(), Qt::KeepAspectRatio);
    m_view_source->show();
    engine = setupEngine(image_path.toStdString());
    contour_num = engine.facts_library.size();
    
}
void Frame::OpenRuleEditBtnSlot() {
    if(m_rule_edit == nullptr) {
        m_rule_edit = new RuleEdit(m_frame_widget);
    }
    m_rule_edit->ShowWindows();
}
void Frame::ShowRulesBtnSlot() {

    if(m_all_rules_widget == nullptr) {
        m_all_rules_widget = new QWidget();
        m_all_rules_widget->setWindowTitle("All Rules");
        m_all_rules_widget->setBaseSize(200, 600);
        QHBoxLayout *m_all_rules_layout = new QHBoxLayout(m_all_rules_widget);

        m_all_rules_text = new QPlainTextEdit(m_all_rules_widget);
        m_all_rules_layout->addWidget(m_all_rules_text);

        
    }
    if(m_all_rules_text) {
        m_all_rules_text->clear();
    }

    std::ifstream infile("../rules/rules.txt");
        if(!infile.is_open()) {
            std::cout << "open file error!" << std::endl;
            return;
        }
        std::string line;
        while(std::getline(infile, line)) {
            if(m_all_rules_text) {
                m_all_rules_text->appendPlainText(line.c_str());
            }
        }
        infile.close();
    
    m_all_rules_widget->show();


}
void Frame::ShowFactsBtnSlot() {
    if(m_all_facts_widget == nullptr) {
        m_all_facts_widget = new QWidget();
        m_all_facts_widget->setWindowTitle("All Facts");
        m_all_facts_widget->setBaseSize(200, 600);
        QHBoxLayout *m_all_facts_layout = new QHBoxLayout(m_all_facts_widget);

        m_all_facts_text = new QPlainTextEdit(m_all_facts_widget);
        m_all_facts_layout->addWidget(m_all_facts_text);

        
    }
    if(m_all_facts_text) {
        m_all_facts_text->clear();
    }

    std::ifstream infile("../facts/facts.txt");
        if(!infile.is_open()) {
            std::cout << "open file error!" << std::endl;
            return;
        }
        std::string line;
        while( std::getline(infile, line)) {
            if(m_all_facts_text) {
                m_all_facts_text->appendPlainText(line.c_str());
            }
        }
        infile.close();
    
    m_all_facts_widget->show();
}

void Frame::QTreeWidgetItemDoubleClickedSlot(QTreeWidgetItem *item, int column) {
    shape_type = item->text(column);
    std::cout << shape_type.toStdString() << "\n";
    if(this->image_path.isEmpty()) {
        std::cout<< "请先选择图像\n";
        return;
    }
    ShapeChosen();
}

void Frame::ShapeChosen() {
    if(shape_type == "" || shape_type == "All Shapes") {
        QMessageBox::information(NULL, "Title", QStringLiteral("请选择具体的图形"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    std::string chosen_shape = "the shape is " + shape_type.toLower().toStdString();

    std::cout << "chosen_shape: " << chosen_shape << "\n";

    setGoal(engine, chosen_shape);

    /* for(int i=0; i<engine.rule_library.size(); i++) {
        std::cout << engine.rule_library[i].toString() << "\n";
    }
    for(auto cntline : engine.facts_library) {
        std::cout << cntline.first + "\n" + cntline.second.toString() << "\n";
    } */


    std::tuple<std::vector<std::string>, std::map<std::string, std::vector<Fact>>, std::map<std::string, std::vector<Rule>>> tuple_res = mainRun(engine);
    
    // std::cout << std::get<0>(tuple_res).size() << std::get<1>(tuple_res).size() << std::get<2>(tuple_res).size() << std::endl;
    cv::Mat source_img = cv::imread(image_path.toStdString());
    // std::cout << source_img.size() << source_img.type() << std::endl;

    cv::Mat detection_image = cv::Mat::zeros(source_img.size(), source_img.type());
    // std::cout << detection_image.size() << detection_image.type() << std::endl;

    DrawLines(detection_image, std::get<1>(tuple_res), contour_num);
    cv::imwrite("../test_images/detection.png", detection_image, {cv::IMWRITE_PNG_COMPRESSION, 0});
    // cv::Mat tem = cv::imread("../test_images/detection.png");
    // std::cout << tem.size() << tem.type() << std::endl;

    m_scene_detection->clear();
    m_scene_detection->addPixmap(QStringLiteral("../test_images/detection.png"));
    m_view_detection->fitInView(m_scene_detection->sceneRect(), Qt::KeepAspectRatio);
    m_view_detection->show();

    m_dection_result_text->clear();
    m_dection_result_text->appendPlainText(QString::fromStdString(GetResult(std::get<0>(tuple_res))));

    m_matched_facts_text->clear();
    m_matched_facts_text->appendPlainText(QString::fromStdString(GetMatchedFacts(std::get<1>(tuple_res), contour_num)));

    m_hit_rules_text->clear();
    m_hit_rules_text->appendPlainText(QString::fromStdString(GetHitRules(std::get<2>(tuple_res), contour_num)));
    // ...
}







/****************************************************************************************************/
/*******************************************Public Function******************************************/
/****************************************************************************************************/
void DrawLines(cv::Mat &img, std::map<std::string, std::vector<Fact>> &facts, int contour_num) {
    for(int i=0; i<contour_num; i++) {
        for(auto fact : facts["Contour" + std::to_string(i)]) {
            for(auto line : fact.about) {
                cv::line(img, line.p1, line.p2, cv::Scalar(0,255,0), 2, cv::LINE_AA);
            }
        }
    }
}

std::string GetResult(std::vector<std::string> result) {
    std::string str="";
    for(int i=0; i<result.size()-1; i++) {
        str += result[i] + "\n";
    }
    str += result[result.size()-1];
    return str;
}

std::string GetMatchedFacts(std::map<std::string, std::vector<Fact>> match_facts, int contour_num) {
    std::string str="";
    for(int i=0; i<contour_num; i++) {
        if( !match_facts["Contour"+std::to_string(i)].empty() ){
            str += "---- Shape " + std::to_string(i) + " ----\n";
        }
        for(auto fact : match_facts["Contour"+std::to_string(i)]) {
            str += fact.fact + "\n";
        }
    }
    return str;
}

std::string GetHitRules(std::map<std::string, std::vector<Rule>> hit_rules, int contour_num) {
    std::string str="";
    for(int i=0; i<contour_num; i++) {
        if( !hit_rules["Contour"+std::to_string(i)].empty() ) {
            str += "---- Shape " + std::to_string(i) + " ----\n";
        }
        for( auto rule : hit_rules["Contour"+std::to_string(i)] ) {
            str += rule.toString();
        }
    }
    return str;
}