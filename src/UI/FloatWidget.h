#ifndef FLOATWIDGET_H
#define FLOATWIDGET_H

#include <QWidget>

namespace Ui
{
    class FloatWidget;
}

class FloatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FloatWidget(QWidget *parent = nullptr);
    explicit FloatWidget(QString &mainPropName, QString &prop1Name, double minVal, double maxVal, QWidget *parent = nullptr);

    ~FloatWidget();
    void SetProp(const double &val);
    void BindData(double *bindPtr);

private:
    Ui::FloatWidget *ui;
    double *prop;
};

#endif // FLOATWIDGET_H
