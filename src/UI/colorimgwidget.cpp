#include "colorimgwidget.h"
#include "ui_colorimgwidget.h"
#include <QDebug>
#include <QColorDialog>
ColorImgWidget::ColorImgWidget(QWidget *parent) : QWidget(parent),
                                                  ui(new Ui::ColorImgWidget), m_color(nullptr)

{
    ui->setupUi(this);
}

ColorImgWidget::ColorImgWidget(QString &name, QWidget *parent) : QWidget(parent),
                                                                 ui(new Ui::ColorImgWidget)
{
    ui->setupUi(this);
    ui->mainprop->setText(name);
}

ColorImgWidget::~ColorImgWidget()
{
    delete ui;
}

void ColorImgWidget::SetProp(const Vec4 &val)
{
    QColor qColor = Vec4ToQColor(val);
    qColor.setRgbF(val.r, val.g, val.b, val.a);
    QString styleSheet = QString("QToolButton { background-color: rgba(%1, %2, %3, %4);"
                                 "  border-radius: 0px; "
                                 "  border: 1px solid rgba(0, 0, 0, 0);"
                                 "  border-radius: 5px; "
                                 "  padding: 5px 10px; "
                                 "}"
                                 "QToolButton:hover { "
                                 "  background-color: rgba(%1, %2, %3, %4); "
                                 "  padding: 6px 9px; "
                                 "  margin: -1px; "
                                 "}")
                             .arg(qColor.red())
                             .arg(qColor.green())
                             .arg(qColor.blue())
                             .arg(qColor.alpha());
    ui->colorButton->setStyleSheet(styleSheet);
}

void ColorImgWidget::BindData(Vec4 *bindPtr)
{
    m_color = bindPtr;
    // connect(ui->spinBox1, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double val)
    //         { if (prop) prop->x = val; });
    connect(ui->colorButton, &QToolButton::clicked, this, [&]()
            {
                QColorDialog colorDlg(this); //设置颜色对话框
                colorDlg.setGeometry(1200,250,300,280);
    colorDlg.setWindowTitle("Color Editor");  //颜色对话框标题
    colorDlg.setCurrentColor(Vec4ToQColor(*m_color));
    if( colorDlg.exec() == QColorDialog::Accepted )
    {
        QColor color = colorDlg.selectedColor();
        *m_color = QColorToVec4(color);
        SetProp(*m_color);
    } });
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
