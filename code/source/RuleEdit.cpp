/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-26 16:11:29
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-11-27 14:35:58
 * @FilePath: /Simple_geometric_expert_system/code/source/RuleEdit.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "../include/RuleEdit.h"
#include <fstream>
#include <qplaintextedit.h>
#include <qpushbutton.h>
#include <qstringliteral.h>

RuleEdit::RuleEdit(QWidget *parent) : QWidget(parent){
    InitWidget();
    InitConnect();
}
RuleEdit::~RuleEdit() {
    if(rule_edit_widget != nullptr) {
        delete rule_edit_widget;
        rule_edit_widget = nullptr;
    }
}

void RuleEdit::InitWidget() {
    if(!rule_edit_widget) {
        rule_edit_widget = new QWidget();
    }
    rule_edit_widget->setBaseSize(400, 300);
    rule_edit_widget->setWindowTitle("Rule Edit");

    QGridLayout *layout = new QGridLayout(rule_edit_widget);
    QLabel *tip = new QLabel(rule_edit_widget);
    tip->setText(QStringLiteral("请在一行只输入一个限制"));
    QLabel *if_label = new QLabel(rule_edit_widget);
    if_label->setText(QStringLiteral("IF:"));
    if_part = new QPlainTextEdit(rule_edit_widget);
    QLabel *then_label = new QLabel(rule_edit_widget);
    then_label->setText(QStringLiteral("THEN:"));
    then_part = new QLineEdit(rule_edit_widget);
    QLabel *description_label = new QLabel(rule_edit_widget);
    description_label->setText(QStringLiteral("DESCRIPTION:"));
    description_part = new QLineEdit(rule_edit_widget);
    create_btn = new QPushButton(rule_edit_widget);
    create_btn->setText(QStringLiteral("Create"));
    cancel_btn = new QPushButton(rule_edit_widget);
    cancel_btn->setText(QStringLiteral("Cancel"));

    layout->addWidget(tip, 0, 0, 1, 4);
    layout->addWidget(if_label, 1, 0, 1, 1);
    layout->addWidget(if_part, 1, 1, 1, 3);
    layout->addWidget(then_label, 2, 0, 1, 1);
    layout->addWidget(then_part, 2, 1, 1,3);
    layout->addWidget(description_label, 3, 0, 1, 1);
    layout->addWidget(description_part, 3, 1, 1, 3);
    layout->addWidget(create_btn, 4, 0, 1, 2);
    layout->addWidget(cancel_btn, 4, 2, 1, 2);
}

void RuleEdit::InitConnect() {
    connect(create_btn, &QPushButton::clicked, this, &RuleEdit::CreateRule_Slot);
    connect(cancel_btn, &QPushButton::clicked, this, &RuleEdit::CancelRule_Slot);

}


void RuleEdit::ShowWindows() {
    this->rule_edit_widget->show();
}

void RuleEdit::CreateRule_Slot() {
    std::ofstream file("../rules/rules.txt", std::ios::app);
    if(!file.is_open()) {
        std::cout << "file open failed\n";
    }
    file << CreateFormattedRule();
    file.close();
}
void RuleEdit::CancelRule_Slot() {
    this->rule_edit_widget->close();
}

std::string RuleEdit::CreateFormattedRule() {
    std::string str;
    str += "{\nIF: [";
    QList<QString> all_text = if_part->toPlainText().split("\n");
    for(int i=0; i<all_text.size()-1; i++) {
        str += "'" + all_text[i].toStdString() + "', ";
    }
    str += "'"+all_text[all_text.size()-1].toStdString() + "']\nTHEN: '";
    str += then_part->text().toStdString() + "'\nDESCRIPTION: '" + description_part->text().toStdString() + "'\n}\n";
    return str;
}
