/*
 * @Author: PapillonAz 1065940593@qq.com
 * @Date: 2023-11-20 11:13:43
 * @LastEditors: PapillonAz 1065940593@qq.com
 * @LastEditTime: 2023-11-27 14:41:30
 * @FilePath: /Simple_geometric_expert_system/code/include/MainWidget.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <qtmetamacros.h>
#include <QMainWindow>

#include "../include/Frame.h"

class MainWindow : public QMainWindow{
    
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void show();

private:
    Frame *m_frame = nullptr;
    
    void InitWindow();

public:

public slots:



};