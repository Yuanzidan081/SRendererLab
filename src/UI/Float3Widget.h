#ifndef FLOAT3WIDGET_H
#define FLOAT3WIDGET_H

#include <QWidget>
#include "Math/Vec3.h"
#include <QDoubleSpinBox>
#include <vector>
namespace Ui
{
    class Float3Widget;
}

class Float3Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Float3Widget(QWidget *parent = nullptr);
    explicit Float3Widget(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, double minVal, double maxVal, QWidget *parent = nullptr);
    ~Float3Widget();
    void SetProp(const Vec3 &val);
    void BindData(Vec3 *bindPtr);

private:
    Ui::Float3Widget *ui;
    Vec3 *prop;
};

#endif // Float3Widget_H
