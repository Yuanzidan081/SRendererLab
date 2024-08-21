#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include <QWidget>

namespace Ui {
class ModelWidget;
}

class ModelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ModelWidget(QWidget *parent = nullptr);
    ~ModelWidget();

private:
    Ui::ModelWidget *ui;
};

#endif // MODELWIDGET_H
