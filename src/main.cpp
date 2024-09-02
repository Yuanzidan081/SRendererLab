// test main.cpp
#include <iostream>
#include <QtWidgets/QApplication>
// #include "UI/View/mainwidget.h"
#include "UI/App/RenderApp.h"
#include "main.h"
int main(int argc, char *argv[])
{
    std::cout << "SRendererLab set up!" << std::endl;
    // config the global variables

    QApplication a(argc, argv);
    RenderApp app;
    app.Run();
    // MainWidget m;
    // m.show();

    return a.exec();
}