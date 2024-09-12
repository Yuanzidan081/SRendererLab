#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include <memory>
#include <QToolButton>
#include <QLabel>
namespace Ui
{
    class ConfigWidget;
}
class Config;
class Texture;
enum class TextureRangeFormat;
class ConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWidget(const std::shared_ptr<Config> &config, QWidget *parent = nullptr);
    ~ConfigWidget();
    void SetSkyBoxImage(int index, QLabel *&lbl);
    void ShowTexture(std::shared_ptr<Texture> &tex, QLabel *&lbl, TextureRangeFormat format);
    void OpenHDRFile();
    void Init();

private:
    Ui::ConfigWidget *ui;

    std::weak_ptr<Config>
        m_config;
};

#endif // CONFIGWIDGET_H
