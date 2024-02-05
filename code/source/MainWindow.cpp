/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-20 11:14:12
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-12-20 14:38:32
 * @FilePath: /Simple_geometric_expert_system/code/source/MainWindow.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <qmainwindow.h>
#include <QHash>

#include "../include/MainWindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    InitWindow();



}

MainWindow::~MainWindow() {
    if(!m_frame) {
        delete m_frame;
    }
}


void MainWindow::show() {
    this->m_frame->ShowWindow();
}


void MainWindow::InitWindow() {
    this->m_frame = new Frame(this);

    // struct KeyValuePair {
    //     QString key;
    //     QString value;
    // };

    // QList<KeyValuePair> keyValueList;
    // KeyValuePair pair1{"z", "1"};
    // KeyValuePair pair2{"x", "2"};
    // KeyValuePair pair3{"y", "3"};

    // keyValueList.append(pair1);
    // keyValueList.append(pair2);
    // keyValueList.append(pair3);

    // for (const KeyValuePair& pair : keyValueList) {
    //     std::cout << pair.key.toStdString() << ": " << pair.value.toStdString() << std::endl;
    // }
}