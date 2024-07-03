// test main.cpp
#include <iostream>
#include <QtWidgets/QApplication>
#include "UI/mainwidget.h"
#include "main.h"
int main(int argc, char *argv[])
{
    std::cout << "SRendererLab set up!" << std::endl;
    // config the global variables
    RendererInit();

    QApplication a(argc, argv);
    MainWidget m;
    m.show();
    return a.exec();
}