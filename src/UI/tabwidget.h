#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QWidget>
#include "Float3Widget.h"
#include "FloatWidget.h"
#include "colorimgwidget.h"
#include <QMap>
#include <QString>
namespace Ui
{
    class TabWidget;
}

class TabWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TabWidget(QWidget *parent = nullptr);
    ~TabWidget();
    void Clear();

    virtual void AddFloat3(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, Vec3 *val, double minVal = -1000.0, double maxVal = 1000.0, const QString &tag = "Default") {}
    virtual void AddFloat(QString &mainPropName, QString &prop1Name, double *val, double minVal = -1000.0, double maxVal = 1000.0, const QString &tag = "Default") {}
    virtual void AddInt(QString &mainPropName, QString &prop1Name, int *val, int minVal = -1000.0, int maxVal = 1000.0, const QString &tag = "Default") {}

private:
    Ui::TabWidget *ui;

protected:
    struct Property
    {
        QMap<QString, FloatWidget *> PropFloat;    // 浮点数 varying 列表
        QMap<QString, Float3Widget *> PropVec3;    // 三维矢量 varying 列表
        QMap<QString, ColorImgWidget *> propColor; // 颜色贴图
    };
    Property propMap;
};

#endif // TABWIDGET_H
