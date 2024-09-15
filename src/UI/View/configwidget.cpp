#include "configwidget.h"
#include "ui_configwidget.h"
#include "Core/Config.h"
#include <QFileDialog>
#include <QCheckBox>
#include "Render/Texture.h"
#include "stdio.h"
#include <iostream>
#include "algorithm/ColorAlgorithm.h"
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
    connect(ui->useSkyBox, static_cast<void (QCheckBox::*)(bool)>(&QCheckBox::clicked), this, &ConfigWidget::UseSkyBoxCheckBoxChanged);
}

ConfigWidget::~ConfigWidget()
{
    delete ui;
}

void ConfigWidget::SetSkyBoxImage(int index, QLabel *&lbl)
{
    QFileDialog *fileDialog = new QFileDialog(this, QString::fromLocal8Bit("Open Texture"), "./res", "*Texture File(*.bmp *.jpg *.jpeg *.png *.tga *.hdr)");
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        std::shared_ptr<Texture> tex = std::make_shared<Texture>(fileNames[0].toStdString());
        m_config.lock()->m_cubeMap->SetTexture(index, tex);
        ShowTexture(tex, lbl, TextureRangeFormat::UNSIGNED_CHAR);
    }
}

void ConfigWidget::ShowTexture(std::shared_ptr<Texture> &tex, QLabel *&lbl, TextureRangeFormat format)
{
    if (tex == nullptr)
    {
        std::cout << "invalid texture- show texture" << std::endl;
        return;
    }
    QImage *tmp;
    if (format == TextureRangeFormat::UNSIGNED_CHAR)
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
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(0), ui->xposImage, TextureRangeFormat::FLOAT);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(1), ui->yposImage, TextureRangeFormat::FLOAT);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(2), ui->zposImage, TextureRangeFormat::FLOAT);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(3), ui->xnegImage, TextureRangeFormat::FLOAT);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(4), ui->ynegImage, TextureRangeFormat::FLOAT);
        ShowTexture(m_config.lock()->m_cubeMap->GetTexture(5), ui->znegImage, TextureRangeFormat::FLOAT);
        ShowIrradianceMap(ui->irradianceImage);

        // ShowTexture(tex, lbl);
    }
}

void ConfigWidget::Init()
{
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(0), ui->xposImage, TextureRangeFormat::UNSIGNED_CHAR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(1), ui->yposImage, TextureRangeFormat::UNSIGNED_CHAR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(2), ui->zposImage, TextureRangeFormat::UNSIGNED_CHAR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(3), ui->xnegImage, TextureRangeFormat::UNSIGNED_CHAR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(4), ui->ynegImage, TextureRangeFormat::UNSIGNED_CHAR);
    ShowTexture(m_config.lock()->m_cubeMap->GetTexture(5), ui->znegImage, TextureRangeFormat::UNSIGNED_CHAR);
    ShowIrradianceMap(ui->irradianceImage);
}

void ConfigWidget::UseSkyBoxCheckBoxChanged(bool checked)
{
    // std::cout << checked << std::endl;
    m_config.lock()->m_useSkyBox = checked;
}

/* diffuse part */
void ConfigWidget::ShowIrradianceMap(QLabel *&lbl)
{

    Vec3 irradiance(0, 0, 0);
    // std::cout << lbl->geometry().width() << " " << lbl->geometry().height();
    int faceMapping[3][4] = {
        {-1, 4, -1, -1},
        {3, 5, 0, 2},
        {-1, 1, -1, -1}};

    int labelWidth = lbl->geometry().width();   // label宽度
    int labelHeight = lbl->geometry().height(); // label高度
    int blockWidth = labelWidth / 4;
    int blockHeight = labelHeight / 3;

    QImage *image = new QImage(labelWidth, labelHeight, QImage::Format_RGB32);

    for (int x = 0; x < labelWidth; x++)
    {
        for (int y = 0; y < labelHeight; y++)
        {
            // 找到当前像素所属的块
            int blockX = x / blockWidth;
            int blockY = y / blockHeight;

            // 根据 blockX 和 blockY 在 faceMapping 中找到对应的面
            int face_id = faceMapping[blockY][blockX];
            // 如果是 -1，填充黑色
            if (face_id == -1)
            {
                // 直接填充黑色
                image->setPixel(x, y, qRgb(255.0f, 255.0f, 255.0f));
                // Vec4 color(0.0f, 0.0f, 0.0f, 1.0f);
                // 设置颜色到label的对应位置
                // image.set(i, j, color); // 假设有image对象
            }
            else
            {
                // 如果是有效的face_id（0-5），我们需要从 CubeMap 采样
                // 计算出立方体映射中的 x 和 y
                int xOffset = x % blockWidth;
                int yOffset = y % blockHeight;
                Vec3 normal = m_config.lock()->m_cubeMap->GetCubeViewWolrdPos(face_id, xOffset, yOffset, blockWidth);
                normal.Normalize();
                Vec3 up = fabs(normal.y) < 0.999f ? Vec3(0.0f, 1.0f, 0.0f) : Vec3(0.0f, 0.0f, 1.0f); // 防止得到0
                Vec3 right = up.GetCrossProduct(normal);
                right.Normalize();
                // tagent x-axis
                up = normal.GetCrossProduct(right); // tagent y-axis

                irradiance = Vec3(0, 0, 0);
                float sampleDelta = 0.1f;
                int numSamples = 0;

                for (float phi = 0.0f; phi < 2.0 * M_PI; phi += sampleDelta)
                {
                    for (float theta = 0.0f; theta < M_PI * 0.5f; theta += sampleDelta)
                    {
                        // spherical to cartesian (in tangent space)
                        Vec3 tangentSample = Vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
                        // tangent space to world
                        Vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal;
                        sampleVec.Normalize();
                        Vec3 color = m_config.lock()->m_cubeMap->SampleCubeMap(sampleVec);

                        irradiance += color * sin(theta) * cos(theta);
                        numSamples++;
                    }
                }
                float weight = M_PI / numSamples;
                irradiance *= weight;
                int r = std::min(255.0f, std::max(0.0f, irradiance.r * 255.0f));
                int g = std::min(255.0f, std::max(0.0f, irradiance.g * 255.0f));
                int b = std::min(255.0f, std::max(0.0f, irradiance.b * 255.0f));
                image->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    // lbl->
    QImage mirroredImage = image->mirrored(false, true);
    lbl->setPixmap(QPixmap::fromImage(mirroredImage));
}
