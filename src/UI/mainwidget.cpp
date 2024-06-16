#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
MainWidget::MainWidget(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MainWidget)

{
    ui->setupUi(this);
    // 设置窗口标志，禁止缩放
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->window, &Window::fpsUpdate, this, &MainWidget::DisplayFps);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::DisplayFps(int fps)
{
    ui->groupBoxWindow->setTitle(QString("fps: %1").arg(fps));
}
