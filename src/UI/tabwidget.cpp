#include "tabwidget.h"
#include "ui_tabwidget.h"

TabWidget::TabWidget(QWidget *parent) : QWidget(parent),
                                        ui(new Ui::TabWidget)
{
    ui->setupUi(this);
}

TabWidget::~TabWidget()
{
    delete ui;
}

void TabWidget::Clear()
{

    for (auto it = propMap.PropVec3.begin(); it != propMap.PropVec3.end(); ++it)
    {
        delete it.value();
        it.value() = nullptr;
    }
    for (auto it = propMap.PropFloat.begin(); it != propMap.PropFloat.end(); ++it)
    {
        delete it.value();
        it.value() = nullptr;
    }
    for (auto it = propMap.propColor.begin(); it != propMap.propColor.end(); ++it)
    {
        delete it.value();
        it.value() = nullptr;
    }
    propMap.PropVec3.clear();
    propMap.PropFloat.clear();
    propMap.propColor.clear();
}
