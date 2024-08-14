#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>

namespace Ui {
class LightWidget;
}

class LightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightWidget(QWidget *parent = nullptr);
    ~LightWidget();

private:
    Ui::LightWidget *ui;
};

#endif // LIGHTWIDGET_H
