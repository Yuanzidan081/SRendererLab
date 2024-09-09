#ifndef COLORIMGWIDGET_H
#define COLORIMGWIDGET_H

#include <QWidget>
#include "Math/Vec4.h"
#include <QFileDialog>

namespace Ui
{
    class ColorImgWidget;
}
class Texture2D;
class ColorImgWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorImgWidget(QWidget *parent = nullptr);
    explicit ColorImgWidget(QString &name, QWidget *parent = nullptr);
    ~ColorImgWidget();

    void SetProp(const Vec4 &val);
    void BindData(Vec4 *bindPtr, std::string *texturePath);
    void OpenColorDialog();
    void SetTextureNone();
    void SetTextureFromFile();

private:
    QColor Vec4ToQColor(const Vec4 &color);
    Vec4 QColorToVec4(const QColor &color);
    void ShowTexture();
    Ui::ColorImgWidget *ui;
    Vec4 *m_color;
    std::string *m_texture;
    Texture2D *m_textureDisplay;
};

#endif // COLORIMGWIDGET_H
