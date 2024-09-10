#include "imagepanel.h"
#include "ui_imagepanel.h"
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include "Render/Texture.h"

ImagePanel::ImagePanel(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::ImagePanel)
{
    ui->setupUi(this);
}

ImagePanel::ImagePanel(QString &name, QWidget *parent) : QWidget(parent),
                                                         ui(new Ui::ImagePanel), m_texture(nullptr), m_textureDisplay(nullptr)
{
    ui->setupUi(this);
    ui->mainprop->setText(name);
    // 创建QMenu
    ui->textureButton->setIcon(QIcon(QString("./res/icon/refresh.png")));
    QMenu *addTextureMenu = new QMenu(ui->textureButton);

    // // 添加动作到QMenu
    QAction *addTextureNone = new QAction("None", addTextureMenu);
    connect(addTextureNone, &QAction::triggered, this, &ImagePanel::SetTextureNone);

    QAction *addTextureFromFile = new QAction("From File", addTextureMenu);
    connect(addTextureFromFile, &QAction::triggered, this, &ImagePanel::SetTextureFromFile);
    addTextureMenu->addAction(addTextureNone);
    addTextureMenu->addAction(addTextureFromFile);

    // // 设置QToolButton的属性以在点击时显示下拉菜单
    ui->textureButton->setMenu(addTextureMenu);
    ui->textureButton->setPopupMode(QToolButton::InstantPopup);
}

ImagePanel::~ImagePanel()
{
    if (m_textureDisplay)
        delete m_textureDisplay;
    m_textureDisplay = nullptr;
    delete ui;
}

void ImagePanel::BindData(std::string *texturePath)
{
    m_texture = texturePath;
    ShowTexture();
}

void ImagePanel::SetTextureNone()
{
    *m_texture = "";
    ShowTexture();
}

void ImagePanel::SetTextureFromFile()
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

void ImagePanel::ShowTexture()
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
