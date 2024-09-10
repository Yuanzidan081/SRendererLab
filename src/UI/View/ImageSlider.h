#ifndef IMAGESLIDER_H
#define IMAGESLIDER_H

#include <QWidget>

namespace Ui
{
    class ImageSlider;
}
class Texture;
class ImageSlider : public QWidget
{
    Q_OBJECT

public:
    explicit ImageSlider(QWidget *parent = nullptr);
    explicit ImageSlider(QString &name, QWidget *parent = nullptr);

    ~ImageSlider();
    void SetProp(const float &val);
    void BindData(float *bindPtr, std::string *texturePath);

    void SetTextureNone();
    void SetTextureFromFile();

private:
    Ui::ImageSlider *ui;
    std::string *m_texture;
    float *m_factor;
    Texture *m_textureDisplay;
    void ShowTexture();

    void ChangeFactorLineEdit();
    void ChangeFactorSlider(const QString &);
};

#endif // IMAGESLIDER_H
