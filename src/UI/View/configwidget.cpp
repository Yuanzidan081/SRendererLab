#include "configwidget.h"
#include "ui_configwidget.h"
#include "Core/Config.h"
#include <QFileDialog>
#include "Render/Texture.h"
#include "stdio.h"
ConfigWidget::ConfigWidget(const std::shared_ptr<Config> &config, QWidget *parent) : QWidget(parent),
                                                                                     ui(new Ui::ConfigWidget),
                                                                                     m_config(config)

{
    // printf("%p\n", config.get());
    // printf("%p\n", m_config.lock());

    ui->setupUi(this);
    connect(ui->xposImageBtn, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [&]()
            { SetSkyBoxImage(0, ui->xposImage); });
    connect(ui->yposImageBtn, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [&]()
            { SetSkyBoxImage(1, ui->yposImage); });
    connect(ui->zposImageBtn, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [&]()
            { SetSkyBoxImage(2, ui->zposImage); });
    connect(ui->xnegImageBtn, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [&]()
            { SetSkyBoxImage(3, ui->xnegImage); });
    connect(ui->ynegImageBtn, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [&]()
            { SetSkyBoxImage(4, ui->ynegImage); });
    connect(ui->znegImageBtn, static_cast<void (QToolButton::*)(bool)>(&QToolButton::clicked), this, [&]()
            { SetSkyBoxImage(5, ui->znegImage); });
    connect(ui->loadHDRBtn, static_cast<void (QPushButton::*)(bool)>(&QPushButton::clicked), this, [&]()
            { OpenHDRFile(); });
}

ConfigWidget::~ConfigWidget()
{
    delete ui;
}

void ConfigWidget::SetSkyBoxImage(int index, QLabel *&lbl)
{
    QFileDialog *fileDialog = new QFileDialog(this, QString::fromLocal8Bit("Open Texture"), "./obj", "*Texture File(*.bmp *.jpg *.jpeg *.png *.tga *.hdr)");
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        std::shared_ptr<Texture> tex = std::make_shared<Texture>(fileNames[0].toStdString());
        m_config.lock()->m_cubeMap->SetTexture(index, tex);
        ShowTexture(tex, lbl, TextureFormat::LDR);
    }
}

void ConfigWidget::ShowTexture(std::shared_ptr<Texture> &tex, QLabel *&lbl, TextureFormat format)
{
    if (tex == nullptr)
    {
        std::cout << "invalid texture- show texture" << std::endl;
        return;
    }
    QImage *tmp;
    if (format == TextureFormat::LDR)
    {
        if (tex->GetChannels() == 3)
            tmp = new QImage(tex->GetTextureDataLDR(), tex->GetWidth(), tex->GetHeight(), QImage::Format_RGB888);
        else if (tex->GetChannels() == 4)
            tmp = new QImage(tex->GetTextureDataLDR(), tex->GetWidth(), tex->GetHeight(), QImage::Format_RGBA8888);
        else if (tex->GetChannels() == 1)
            tmp = new QImage(tex->GetTextureDataLDR(), tex->GetWidth(), tex->GetHeight(), QImage::Format_Grayscale8);
    }
    else
    {
        // std::cout << tex->GetWidth() << " " << tex->GetHeight() << std::endl;
        tmp = new QImage(tex->GetWidth(), tex->GetHeight(), QImage::Format_RGB32);
        float deltaY = 1.0f / (float)tex->GetHeight();
        float deltaX = 1.0f / (float)tex->GetWidth();
        int h = tex->GetHeight();
        int w = tex->GetWidth();
        for (float y = 0; y < 1.0f; y += deltaY)
        {
            for (float x = 0; x < 1.0f; x += deltaX)
            {
                // const Imf::Rgba &px = pixels[y][x];
                Vec4 px = tex->SampleTexture(Vec2(x, y));
                // 简单的色调映射，将HDR值映射到0-255
                int r = std::min(255.0f, std::max(0.0f, px.r * 255.0f));
                int g = std::min(255.0f, std::max(0.0f, px.g * 255.0f));
                int b = std::min(255.0f, std::max(0.0f, px.b * 255.0f));
                tmp->setPixel(Clamp((int)(x * w), 0, w), Clamp((int)(y * h), 0, h), qRgb(r, g, b));
            }
        }
    }

    QImage image = tmp->scaled(lbl->geometry().width(), lbl->geometry().height());
    QImage mirroredImage = image.mirrored(false, true);
    lbl->setPixmap(QPixmap::fromImage(mirroredImage));
}

void ConfigWidget::OpenHDRFile()
{
    QFileDialog *fileDialog = new QFileDialog(this, QString::fromLocal8Bit("Open HDR"), "./res/hdr", "*HDR File(*.hdr)");
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        m_config.lock()->m_cubeMap = std::make_shared<CubeMap>(fileNames[0].toStdString());
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(0), ui->xposImage, TextureFormat::HDR);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(1), ui->yposImage, TextureFormat::HDR);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(2), ui->zposImage, TextureFormat::HDR);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(3), ui->xnegImage, TextureFormat::HDR);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(4), ui->ynegImage, TextureFormat::HDR);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(5), ui->znegImage, TextureFormat::HDR);
        // ShowTexture(tex, lbl);
    }
}

void ConfigWidget::Init()
{
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(0), ui->xposImage, TextureFormat::LDR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(1), ui->yposImage, TextureFormat::LDR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(2), ui->zposImage, TextureFormat::LDR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(3), ui->xnegImage, TextureFormat::LDR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(4), ui->ynegImage, TextureFormat::LDR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(5), ui->znegImage, TextureFormat::LDR);
}
