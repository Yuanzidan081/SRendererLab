#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
// #include "window.h"
#include "imageWidget.h"
#include "Core/Application.h"
#include "Core/Config.h"
#include <QStandardItemModel>
namespace Ui
{
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void DisplayFps();

    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
public slots:
    void DisplayTreeNode();

private:
    Ui::MainWidget *ui;

    Application *m_app;
    QThread *m_appThread;
    QTimer *m_timer;
    Config *m_config;
    QStandardItemModel *itemMdl;
};

#endif // MAINWIDGET_H
