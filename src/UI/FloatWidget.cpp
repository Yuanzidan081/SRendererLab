#include "FloatWidget.h"
#include "ui_FloatWidget.h"

FloatWidget::FloatWidget(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::FloatWidget)
{
    ui->setupUi(this);
}

FloatWidget::FloatWidget(QString &mainPropName, QString &prop1Name, double minVal, double maxVal, QWidget *parent) : QWidget(parent),
                                                                                                                     ui(new Ui::FloatWidget)
{
    ui->setupUi(this);
    ui->mainprop->setText(mainPropName);
    ui->subprop1->setText(prop1Name);
    ui->spinBox1->setMaximum(maxVal);
    ui->spinBox1->setMinimum(minVal);
}

FloatWidget::~FloatWidget()
{
    delete ui;
}

void FloatWidget::SetProp(const double &val)
{
    ui->spinBox1->setValue(val);
}

void FloatWidget::BindData(double *bindPtr)
{
    prop = bindPtr;
    connect(ui->spinBox1, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double val)
            { if (prop) *prop = val; });
}
