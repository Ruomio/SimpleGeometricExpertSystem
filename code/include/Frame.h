/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-26 16:10:52
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-12-06 17:57:54
 * @FilePath: /Simple_geometric_expert_system/code/include/Frame.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _FRAME_H__
#define _FRAME_H__

#include <iostream>
#include <fstream>
#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTreeWidget>
#include <QPushButton>
#include <qfiledialog.h>
#include <qgridlayout.h>
#include <qplaintextedit.h>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>


#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>


#include "../include/RuleEdit.h"
#include "../include/Engine.h"



class Frame : public QWidget {
  
    Q_OBJECT

public:
    explicit Frame(QWidget *parent = nullptr);
    ~Frame();


    void ShowWindow();


private:
    void InitWindow();
    void InitConnect();
    void ShapeChosen();


private:
    Engine engine;


private:
    QWidget *m_frame_widget = nullptr;
    RuleEdit *m_rule_edit = nullptr;

    QWidget *m_all_rules_widget = nullptr;
    QWidget *m_all_facts_widget = nullptr;

    QPlainTextEdit *m_all_rules_text = nullptr;
    QPlainTextEdit *m_all_facts_text = nullptr;


    QGridLayout *m_layout = nullptr;
    
    QLabel *m_source_label = nullptr;
    QLabel *m_detection_label = nullptr;
    QLabel *m_dection_result_label = nullptr;
    QLabel *m_matched_facts_label = nullptr;
    QLabel *m_hit_rules_label = nullptr;

    QGraphicsScene *m_scene_source = nullptr;
    QGraphicsScene *m_scene_detection = nullptr;
    QGraphicsView *m_view_source = nullptr;
    QGraphicsView *m_view_detection = nullptr;

    QPushButton *m_open_image = nullptr;
    QPushButton *m_open_rule_edit = nullptr;
    QPushButton *m_show_rules = nullptr;
    QPushButton *m_show_facts = nullptr;
    QLabel *m_label_shape = nullptr;
    QTreeWidget *m_tree_widget = nullptr;

    QPlainTextEdit *m_dection_result_text = nullptr;
    QPlainTextEdit *m_matched_facts_text = nullptr;
    QPlainTextEdit *m_hit_rules_text = nullptr;

    QFileDialog *m_file_dialog = nullptr;
    QString image_path;
    QString shape_type;
    int contour_num;

public slots:

    void OpenSourceBtnSlot();
    void OpenRuleEditBtnSlot();
    void ShowRulesBtnSlot();
    void ShowFactsBtnSlot();
    void QTreeWidgetItemDoubleClickedSlot(QTreeWidgetItem *item, int column);
};


void DrawLines(cv::Mat &img, std::map<std::string, std::vector<Fact>> &match_facts, int contour_num);

std::string GetResult(std::vector<std::string> result);

std::string GetMatchedFacts(std::map<std::string, std::vector<Fact>> match_facts, int contour_num);

std::string GetHitRules(std::map<std::string, std::vector<Rule>> hit_rules, int contour_num);

#endif /* _FRAME_H__ */