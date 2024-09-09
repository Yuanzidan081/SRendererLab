#include "colorimgwidget.h"
#include "ui_colorimgwidget.h"
#include <QDebug>
#include <QColorDialog>
#include "Render/Texture2D.h"
#include <QMenu>
#include <QAction>
ColorImgWidget::ColorImgWidget(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::ColorImgWidget), m_color(nullptr), m_texture(nullptr), m_textureDisplay(nullptr)

{
    ui->setupUi(this);
}

ColorImgWidget::ColorImgWidget(QString &name, QWidget *parent) : QWidget(parent),
                                                                 ui(new Ui::ColorImgWidget), m_color(nullptr), m_texture(nullptr), m_textureDisplay(nullptr)
{
    ui->setupUi(this);
    ui->mainprop->setText(name);
    // 创建QMenu
    ui->textureButton->setIcon(QIcon(QString("./res/icon/refresh.png")));
    QMenu *addTextureMenu = new QMenu(ui->textureButton);

    // // 添加动作到QMenu
    QAction *addTextureNone = new QAction("None", addTextureMenu);
    connect(addTextureNone, &QAction::triggered, this, &ColorImgWidget::SetTextureNone);

    QAction *addTextureFromFile = new QAction("From File", addTextureMenu);
    connect(addTextureFromFile, &QAction::triggered, this, &ColorImgWidget::SetTextureFromFile);
    addTextureMenu->addAction(addTextureNone);
    addTextureMenu->addAction(addTextureFromFile);

    // // 设置QToolButton的属性以在点击时显示下拉菜单
    ui->textureButton->setMenu(addTextureMenu);
    ui->textureButton->setPopupMode(QToolButton::InstantPopup);
}

ColorImgWidget::~ColorImgWidget()
{

    if (m_textureDisplay)
        delete m_textureDisplay;
    m_textureDisplay = nullptr;
    delete ui;
}

void ColorImgWidget::SetProp(const Vec4 &val)
{
    QColor qColor = Vec4ToQColor(val);
    qColor.setRgbF(val.r, val.g, val.b, val.a);
    QString styleSheetColor = QString("QToolButton { background-color: rgba(%1, %2, %3, %4);"
                                      "  border-radius: 0px; "
                                      "  border: 1px solid rgb(220, 220, 220);"
                                      "  padding: 5px 10px; "
                                      "}"
                                      "QToolButton:hover { "
                                      "  background-color: rgba(%1, %2, %3, %4); "
                                      "  border: 1px solid rgb(220, 220, 220);"
                                      "  padding: 6px 9px; "
                                      "  margin: -1px; "
                                      "}")
                                  .arg(qColor.red())
                                  .arg(qColor.green())
                                  .arg(qColor.blue())
                                  .arg(qColor.alpha());

    ui->colorButton->setStyleSheet(styleSheetColor);
}

void ColorImgWidget::BindData(Vec4 *bindPtr, std::string *texturePath)
{
    m_color = bindPtr;
    connect(ui->colorButton, &QToolButton::clicked, this, &ColorImgWidget::OpenColorDialog);
    m_texture = texturePath;
    ShowTexture();
}

void ColorImgWidget::OpenColorDialog()
{
    QColorDialog colorDlg(this); // 设置颜色对话框
    colorDlg.setGeometry(1200, 250, 300, 280);
    colorDlg.setWindowTitle("Color Editor"); // 颜色对话框标题
    colorDlg.setCurrentColor(Vec4ToQColor(*m_color));
    if (colorDlg.exec() == QColorDialog::Accepted)
    {
        QColor color = colorDlg.selectedColor();
        *m_color = QColorToVec4(color);
        SetProp(*m_color);
    }
}

void ColorImgWidget::SetTextureNone()
{
    // TODO: concurrency

    *m_texture = "";
    ShowTexture();
}

void ColorImgWidget::SetTextureFromFile()
{
    // sys->mutex.lock();
    QFileDialog *fileDialog = new QFileDialog(this, QString::fromLocal8Bit("打开纹理"), "./obj", "*Texture File(*.bmp *.jpg *.jpeg *.png *.tga *.hdr)");
    // fileDialog->setWindowTitle(QStringLiteral("打开纹理"));
    // fileDialog->setDirectory(".");
    // fileDialog->setNameFilter(tr("Texture File(*.bmp *.jpg *.jpeg *.png *.tga *.hdr)"));
    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        *m_texture = fileNames[0].toStdString();
        // Texture2D *tex = new Texture2D(fileNames[0].toStdString());
        // material->SetTexture(tex, 0);
        // ShowTexture(tex, ui.mCav);
        ShowTexture();
        // delete tex;
    }
    // sys->mutex.unlock();
}

QColor ColorImgWidget::Vec4ToQColor(const Vec4 &color)
{
    QColor qColor;
    qColor.setRgbF(color.r, color.g, color.b, color.a);
    return qColor;
}

Vec4 ColorImgWidget::QColorToVec4(const QColor &color)
{
    Vec4 result;
    result.r = color.redF();
    result.g = color.greenF();
    result.b = color.blueF();
    result.a = color.alphaF();
    return result;
}

void ColorImgWidget::ShowTexture()
{
    if (*m_texture == "")
    {
        ui->imageLabel->setPixmap(QPixmap());
        return;
    }
    if (m_textureDisplay)
        delete m_textureDisplay;
    m_textureDisplay = new Texture2D(*m_texture);

    QImage *tmp;
    if (m_textureDisplay->GetChannels() == 3)
        tmp = new QImage(m_textureDisplay->GetTextureData(), m_textureDisplay->GetWidth(), m_textureDisplay->GetHeight(), QImage::Format_RGB888);
    else if (m_textureDisplay->GetChannels() == 4)
        tmp = new QImage(m_textureDisplay->GetTextureData(), m_textureDisplay->GetWidth(), m_textureDisplay->GetHeight(), QImage::Format_RGBA8888);
    else if (m_textureDisplay->GetChannels() == 1)
        tmp = new QImage(m_textureDisplay->GetTextureData(), m_textureDisplay->GetWidth(), m_textureDisplay->GetHeight(), QImage::Format_Grayscale8);
    QImage image = tmp->scaled(100, 100);
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
}
