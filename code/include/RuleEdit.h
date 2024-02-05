/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-26 16:11:20
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-11-27 14:33:06
 * @FilePath: /Simple_geometric_expert_system/code/include/RuleEdit.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _RULE_EDIT_H__
#define _RULE_EDIT_H__

#include <iostream>
#include <QWidget>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class RuleEdit : public QWidget
{
    Q_OBJECT
    
public:
    explicit RuleEdit(QWidget *parent = nullptr);
    ~RuleEdit();

    void InitWidget();
    void InitConnect();
    void ShowWindows();
    std::string CreateFormattedRule();

private:
    QWidget *rule_edit_widget = nullptr;
    QPushButton *create_btn = nullptr;
    QPushButton *cancel_btn = nullptr;
    QPlainTextEdit *if_part = nullptr;
    QLineEdit *then_part = nullptr;
    QLineEdit *description_part = nullptr;


signals:

public slots:
    void CreateRule_Slot();
    void CancelRule_Slot();



};

#endif