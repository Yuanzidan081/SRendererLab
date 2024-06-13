// test main.cpp
#include <iostream>
#include <QtWidgets/QApplication>
#include "UI/mainwidget.h"
int main(int argc, char *argv[])
{
    std::cout << "SRendererLab set up!" << std::endl;
    QApplication a(argc, argv);
    MainWidget m;
    m.show();
    return a.exec();
}