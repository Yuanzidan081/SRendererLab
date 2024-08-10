#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
// #include "window.h"
#include "imageWidget.h"
#include "Core/Application.h"
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

private:
    Ui::MainWidget *ui;

    Application *m_app;
    QThread *m_appThread;
    QTimer *m_timer;
};

#endif // MAINWIDGET_H
