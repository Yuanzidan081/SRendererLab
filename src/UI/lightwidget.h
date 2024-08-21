#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include "Render/Light.h"
#include "Math/MathGroup.h"
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QMap>
#include <QString>
#include "Float3Widget.h"
#include "FloatWidget.h"
namespace Ui
{
    class LightWidget;
}

class LightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LightWidget(QWidget *parent = nullptr);
    ~LightWidget();
    void Clear();
    void SetModel(QStandardItemModel *model, int selectedIndex, int lightNum);
    void AddFloat3(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, Light *&light, Vec3 *val, double minVal = -1000.0, double maxVal = 1000.0);
    void AddFloat(QString &mainPropName, QString &prop1Name, Light *&light, double *val, double minVal = -1000.0, double maxVal = 1000.0);

signals:
    void ChangeSelectedLight(int selectedIndex);

private:
    Ui::LightWidget *ui;
    QVBoxLayout *lightPropLayout;
    struct Property
    {
        QMap<QString, FloatWidget *> PropFloat; // 浮点数 varying 列表
        QMap<QString, Float3Widget *> PropVec3; // 三维矢量 varying 列表
    };
    Property propMap;
};

#endif // LIGHTWIDGET_H
