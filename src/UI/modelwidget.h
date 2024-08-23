#ifndef MODELWIDGET_H
#define MODELWIDGET_H

#include "tabwidget.h"
#include <QVBoxLayout>

namespace Ui
{
    class ModelWidget;
}

class ModelWidget : public TabWidget
{
    Q_OBJECT

public:
    explicit ModelWidget(QWidget *parent = nullptr);
    ~ModelWidget();
    QVBoxLayout *&GetTargetVBoxLayout(const QString &tag);

    void AddFloat3(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, Vec3 *val, double minVal = -1000.0, double maxVal = 1000.0, const QString &tag = "Default") override;
    void AddFloat(QString &mainPropName, QString &prop1Name, double *val, double minVal = -1000.0, double maxVal = 1000.0, const QString &tag = "Default") override;
    void AddInt(QString &mainPropName, QString &prop1Name, int *val, int minVal = -1000.0, int maxVal = 1000.0, const QString &tag = "Default") override;
    void AddColorImg3(QString &mainPropName, Vec4 *color, const QString &tag);

private:
    Ui::ModelWidget *ui;
    QVBoxLayout *modelTransformPropLayout;
    QVBoxLayout *modelMeshInfoLayout;
    QVBoxLayout *modelMaterialPropLayout;
};

#endif // MODELWIDGET_H
