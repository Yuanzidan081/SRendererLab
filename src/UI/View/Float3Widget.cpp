#include "Float3Widget.h"
#include "ui_float3widget.h"

Float3Widget::Float3Widget(QWidget *parent) : QWidget(parent),
                                              ui(new Ui::Float3Widget), prop(nullptr)
{
    ui->setupUi(this);
}

Float3Widget::Float3Widget(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, double minVal, double maxVal, QWidget *parent) : QWidget(parent),
                                                                                                                                                               ui(new Ui::Float3Widget)
{
    ui->setupUi(this);
    ui->mainprop->setText(mainPropName);
    ui->subprop1->setText(prop1Name);
    ui->subprop2->setText(prop2Name);
    ui->subprop3->setText(prop3Name);
    ui->spinBox1->setMaximum(maxVal);
    ui->spinBox2->setMaximum(maxVal);
    ui->spinBox3->setMaximum(maxVal);
    ui->spinBox1->setMinimum(minVal);
    ui->spinBox2->setMinimum(minVal);
    ui->spinBox3->setMinimum(minVal);
}

Float3Widget::~Float3Widget()
{
    delete ui;
}

void Float3Widget::SetProp(const Vec3 &val)
{
    ui->spinBox1->setValue(val.x);
    ui->spinBox2->setValue(val.y);
    ui->spinBox3->setValue(val.z);
}

void Float3Widget::BindData(Vec3 *bindPtr)
{
    prop = bindPtr;
    connect(ui->spinBox1, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double val)
            { if (prop) prop->x = val; });
    connect(ui->spinBox2, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double val)
            { if (prop) prop->y = val; });
    connect(ui->spinBox3, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [this](double val)
            { if (prop) prop->z = val; });
}
