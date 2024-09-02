#include "colorwidget.h"
#include "ui_colorwidget.h"

#include <QColorDialog>
#include "Render/Texture2D.h"
#include <QMenu>
#include <QAction>

ColorWidget::ColorWidget(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::ColorWidget)
{
    ui->setupUi(this);
}

ColorWidget::ColorWidget(QString &name, QWidget *parent) : QWidget(parent),
                                                           ui(new Ui::ColorWidget)
{
    ui->setupUi(this);
    ui->mainprop->setText(name);
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

void ColorWidget::SetProp(const Vec4 &val)
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

void ColorWidget::BindData(Vec4 *bindPtr)
{
    m_color = bindPtr;
    connect(ui->colorButton, &QToolButton::clicked, this, &ColorWidget::OpenColorDialog);
}

void ColorWidget::OpenColorDialog()
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

QColor ColorWidget::Vec4ToQColor(const Vec4 &color)
{
    QColor qColor;
    qColor.setRgbF(color.r, color.g, color.b, color.a);
    return qColor;
}

Vec4 ColorWidget::QColorToVec4(const QColor &color)
{
    Vec4 result;
    result.r = color.redF();
    result.g = color.greenF();
    result.b = color.blueF();
    result.a = color.alphaF();
    return result;
}
