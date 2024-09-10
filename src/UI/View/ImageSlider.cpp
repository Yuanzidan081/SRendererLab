#include "ImageSlider.h"
#include "ui_imageslider.h"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include "Render/Texture.h"
ImageSlider::ImageSlider(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::ImageSlider)
{
    ui->setupUi(this);
}

ImageSlider::ImageSlider(QString &name, QWidget *parent) : QWidget(parent),
                                                           ui(new Ui::ImageSlider), m_texture(nullptr), m_factor(nullptr), m_textureDisplay(nullptr)
{
    ui->setupUi(this);
    ui->mainprop->setText(name);
    // 创建QMenu
    ui->textureButton->setIcon(QIcon(QString("./res/icon/refresh.png")));
    QMenu *addTextureMenu = new QMenu(ui->textureButton);

    // // 添加动作到QMenu
    QAction *addTextureNone = new QAction("None", addTextureMenu);
    connect(addTextureNone, &QAction::triggered, this, &ImageSlider::SetTextureNone);

    QAction *addTextureFromFile = new QAction("From File", addTextureMenu);
    connect(addTextureFromFile, &QAction::triggered, this, &ImageSlider::SetTextureFromFile);
    addTextureMenu->addAction(addTextureNone);
    addTextureMenu->addAction(addTextureFromFile);

    // // 设置QToolButton的属性以在点击时显示下拉菜单
    ui->textureButton->setMenu(addTextureMenu);
    ui->textureButton->setPopupMode(QToolButton::InstantPopup);
}

ImageSlider::~ImageSlider()
{
    if (m_textureDisplay)
        delete m_textureDisplay;
    m_textureDisplay = nullptr;
    delete ui;
}

void ImageSlider::SetProp(const float &val)
{
    double factor = (double)ui->factorSlider->minimum() + val * ((double)ui->factorSlider->maximum() - (double)ui->factorSlider->minimum());
    ui->factorSlider->setValue(factor);
    ui->factorLineEdit->setText(QString::number(val, 'g', 3));
}

void ImageSlider::BindData(float *bindPtr, std::string *texturePath)
{
    m_factor = bindPtr;
    // connect(ui->colorButton, &QToolButton::clicked, this, &ColorImgWidget::OpenColorDialog);
    connect(ui->factorSlider, &QSlider::valueChanged, this, &ImageSlider::ChangeFactorLineEdit);
    // connect(ui->factorLineEdit, &QLineEdit::textChanged, this, &ImageSlider::ChangeFactorSlider);
    connect(ui->factorLineEdit, static_cast<void (QLineEdit::*)(const QString &)>(&QLineEdit::textChanged),
            this, static_cast<void (ImageSlider::*)(const QString &)>(&ImageSlider::ChangeFactorSlider));
    m_texture = texturePath;
    ShowTexture();
}

void ImageSlider::SetTextureNone()
{
    *m_texture = "";
    ShowTexture();
}

void ImageSlider::SetTextureFromFile()
{
    QFileDialog *fileDialog = new QFileDialog(this, QString::fromLocal8Bit("打开纹理"), "./obj", "*Texture File(*.bmp *.jpg *.jpeg *.png *.tga *.hdr)");
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        *m_texture = fileNames[0].toStdString();
        ShowTexture();
    }
}

void ImageSlider::ShowTexture()
{

    if (*m_texture == "")
    {
        ui->imageLabel->setPixmap(QPixmap());
        return;
    }
    if (m_textureDisplay)
        delete m_textureDisplay;
    m_textureDisplay = new Texture(*m_texture);

    QImage *tmp;
    if (m_textureDisplay->GetChannels() == 3)
        tmp = new QImage(m_textureDisplay->GetTextureDataLDR(), m_textureDisplay->GetWidth(), m_textureDisplay->GetHeight(), QImage::Format_RGB888);
    else if (m_textureDisplay->GetChannels() == 4)
        tmp = new QImage(m_textureDisplay->GetTextureDataLDR(), m_textureDisplay->GetWidth(), m_textureDisplay->GetHeight(), QImage::Format_RGBA8888);
    else if (m_textureDisplay->GetChannels() == 1)
        tmp = new QImage(m_textureDisplay->GetTextureDataLDR(), m_textureDisplay->GetWidth(), m_textureDisplay->GetHeight(), QImage::Format_Grayscale8);
    // QImage image = tmp->scaled(100, 100);
    // ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    QImage image = tmp->scaled(ui->imageLabel->geometry().width(), ui->imageLabel->geometry().height());
    QImage mirroredImage = image.mirrored(false, true);
    ui->imageLabel->setPixmap(QPixmap::fromImage(mirroredImage));
}

void ImageSlider::ChangeFactorLineEdit()
{
    double factor = ((double)ui->factorSlider->value() - (double)ui->factorSlider->minimum()) / ((double)ui->factorSlider->maximum() - (double)ui->factorSlider->minimum());
    ui->factorLineEdit->setText(QString::number(factor, 'g', 3));
    *m_factor = factor;
}

void ImageSlider::ChangeFactorSlider(const QString &str)
{
    double factor = str.toDouble();
    if (factor > 1)
    {
        factor = 1;
        ui->factorLineEdit->setText(QString::number(factor, 'g', 3));
    }
    else if (factor < 0)
    {
        factor = 0;
        ui->factorLineEdit->setText(QString::number(factor, 'g', 3));
    }
    int sliderValue = (double)ui->factorSlider->minimum() + factor * ((double)ui->factorSlider->maximum() - (double)ui->factorSlider->minimum());
    ui->factorSlider->setValue(sliderValue);
    *m_factor = factor;
}
