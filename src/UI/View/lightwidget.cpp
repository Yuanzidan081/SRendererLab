#include "lightwidget.h"
#include "ui_lightwidget.h"
#include <QMenu>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
LightWidget::LightWidget(QWidget *parent) : TabWidget(parent),
                                            ui(new Ui::LightWidget)
{
    ui->setupUi(this);
    Clear();
    lightPropLayout = new QVBoxLayout();
    lightPropLayout->setAlignment(Qt::AlignTop);
    lightPropLayout->setSpacing(3);
    ui->propWidget->setLayout(lightPropLayout);
    ui->addToolButton->setIcon(QIcon(QString("./res/icon/addIcon.png")));
    ui->removeToolButton->setIcon(QIcon(QString("./res/icon/minusIcon.png")));

    QMenu *addToolButtonMenu = new QMenu(ui->addToolButton);

    QAction *addDirectionLight = new QAction("directional light", addToolButtonMenu);
    QAction *addPointLight = new QAction("point light", addToolButtonMenu);
    QAction *addSpotLight = new QAction("spot light", addToolButtonMenu);
    addToolButtonMenu->addAction(addDirectionLight);
    addToolButtonMenu->addAction(addPointLight);
    addToolButtonMenu->addAction(addSpotLight);

    ui->addToolButton->setMenu(addToolButtonMenu);
    ui->addToolButton->setPopupMode(QToolButton::InstantPopup);

    connect(ui->lightListView, &QListView::pressed, [&](QModelIndex pos)
            { emit ChangeSelectedLight(pos.row()); });
}

LightWidget::~LightWidget()
{
    Clear();
    delete ui;
}

void LightWidget::SetModel(QStandardItemModel *model, int selectedIndex)
{
    ui->lightListView->setModel(model);

    // // default: if not select, select 0
    if (selectedIndex == -1)
        return;
}
void LightWidget::AddFloat3(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, Vec3 *val, double minVal, double maxVal, const QString &tag)
{
    Float3Widget *propWidget = new Float3Widget(mainPropName, prop1Name, prop2Name, prop3Name, minVal, maxVal, this);
    propWidget->SetProp(*val);
    propMap.PropVec3.insert(QString(mainPropName), propWidget);
    lightPropLayout->addWidget(propWidget);
    propWidget->BindData(val);
}

void LightWidget::AddFloat(QString &mainPropName, QString &prop1Name, double *val, double minVal, double maxVal, const QString &tag)
{
    FloatWidget *propWidget = new FloatWidget(mainPropName, prop1Name, minVal, maxVal, this);
    propWidget->SetProp(*val);
    propMap.PropFloat.insert(QString(mainPropName), propWidget);
    lightPropLayout->addWidget(propWidget);
    propWidget->BindData(val);
}

// void LightWidget::AddColorImg3(QString &mainPropName, Vec4 *color)
// {
//     ColorImgWidget *propWidget = new ColorImgWidget(mainPropName);
//     propWidget->SetProp(*color);
//     propMap.propColorTexture.insert(QString(mainPropName), propWidget);
//     lightPropLayout->addWidget(propWidget);
//     propWidget->BindData(color);
// }

void LightWidget::AddColor(QString &mainPropName, Vec4 *color)
{
    ColorWidget *propWidget = new ColorWidget(mainPropName);
    propWidget->SetProp(*color);
    propMap.propColor.insert(QString(mainPropName), propWidget);
    lightPropLayout->addWidget(propWidget);
    propWidget->BindData(color);
}
