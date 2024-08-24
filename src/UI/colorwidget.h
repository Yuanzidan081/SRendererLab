#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>
#include "Math/Vec4.h"
namespace Ui
{
    class ColorWidget;
}

class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorWidget(QWidget *parent = nullptr);
    explicit ColorWidget(QString &name, QWidget *parent = nullptr);
    ~ColorWidget();

    void SetProp(const Vec4 &val);
    void BindData(Vec4 *bindPtr);
    void OpenColorDialog();

private:
    QColor Vec4ToQColor(const Vec4 &color);
    Vec4 QColorToVec4(const QColor &color);

    Ui::ColorWidget *ui;
    Vec4 *m_color;
};

#endif // COLORWIDGET_H
