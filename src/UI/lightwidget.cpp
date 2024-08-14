#include "lightwidget.h"
#include "ui_lightwidget.h"

LightWidget::LightWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightWidget)
{
    ui->setupUi(this);
}

LightWidget::~LightWidget()
{
    delete ui;
}
