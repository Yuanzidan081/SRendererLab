#include "colorimgwidget.h"
#include "ui_colorimgwidget.h"
#include <QDebug>
#include <QColorDialog>
#include "Render/Texture2D.h"
#include <QMenu>
#include <QAction>
ColorImgWidget::ColorImgWidget(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::ColorImgWidget), m_color(nullptr), m_texture(nullptr)

{
    ui->setupUi(this);
}

ColorImgWidget::ColorImgWidget(QString &name, QWidget *parent) : QWidget(parent),
                                                                 ui(new Ui::ColorImgWidget)
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
    connect(addTextureNone, &QAction::triggered, this, &ColorImgWidget::SetTextureFromFile);
    addTextureMenu->addAction(addTextureNone);
    addTextureMenu->addAction(addTextureFromFile);

    // // 设置QToolButton的属性以在点击时显示下拉菜单
    ui->textureButton->setMenu(addTextureMenu);
    ui->textureButton->setPopupMode(QToolButton::InstantPopup);
}

ColorImgWidget::~ColorImgWidget()
{
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

void ColorImgWidget::BindData(Vec4 *bindPtr, Texture2D *texture)
{
    m_color = bindPtr;
    connect(ui->colorButton, &QToolButton::clicked, this, &ColorImgWidget::OpenColorDialog);
    m_texture = texture;
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
    // if (m_texture)
    // {
    //     m_texture = nullptr;
    //     using std::swap;
    //     swap(m_texture, )
    //     delete m_texture;

    //     }
}

void ColorImgWidget::SetTextureFromFile()
{
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
