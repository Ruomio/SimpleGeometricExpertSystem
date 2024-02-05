/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-18 11:19:46
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-11-22 14:53:13
 * @FilePath: /Simple_geometric_expert_system/code/source/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <QApplication>

#include "../include/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
