#ifndef IMAGEPANEL_H
#define IMAGEPANEL_H

#include <QWidget>

namespace Ui
{
    class ImagePanel;
}

class Texture;
class ImagePanel : public QWidget
{
    Q_OBJECT

public:
    explicit ImagePanel(QWidget *parent = nullptr);
    ~ImagePanel();
    explicit ImagePanel(QString &name, QWidget *parent = nullptr);

    void SetProp(const float &val);
    void BindData(std::string *texturePath);

    void SetTextureNone();
    void SetTextureFromFile();

private:
    Ui::ImagePanel *ui;
    std::string *m_texture;
    Texture *m_textureDisplay;
    void ShowTexture();
};

#endif // IMAGEPANEL_H
