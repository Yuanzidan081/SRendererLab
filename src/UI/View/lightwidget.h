#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QStandardItemModel>
#include "Math/MathGroup.h"
#include <QVBoxLayout>
#include "tabwidget.h"
namespace Ui
{
    class LightWidget;
}

class LightWidget : public TabWidget
{
    Q_OBJECT

public:
    explicit LightWidget(QWidget *parent = nullptr);
    ~LightWidget();
    void SetModel(QStandardItemModel *model, int selectedIndex);

    void AddFloat3(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, Vec3 *val, double minVal = -1000.0, double maxVal = 1000.0, const QString &tag = "Default") override;
    void AddFloat(QString &mainPropName, QString &prop1Name, double *val, double minVal = -1000.0, double maxVal = 1000.0, const QString &tag = "Default") override;
    // void AddColorImg3(QString &mainPropName, Vec4 *color);
    void AddColor(QString &mainPropName, Vec4 *color);
signals:
    void ChangeSelectedLight(int selectedIndex);

private:
    Ui::LightWidget *ui;
    QVBoxLayout *lightPropLayout;
};

#endif // LIGHTWIDGET_H
