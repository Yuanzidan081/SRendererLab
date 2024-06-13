#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "window.h"
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

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
