#include "lightwidget.h"
#include "ui_lightwidget.h"
#include <QMenu>
#include <QDebug>
#include <QGraphicsDropShadowEffect>
LightWidget::LightWidget(QWidget *parent) : QWidget(parent),
                                            ui(new Ui::LightWidget)
{
    ui->setupUi(this);
    Clear();
    lightPropLayout = new QVBoxLayout();
    lightPropLayout->setAlignment(Qt::AlignTop);
    ui->propWidget->setLayout(lightPropLayout);
    ui->addToolButton->setIcon(QIcon(QString("./res/icon/addIcon.png")));
    ui->removeToolButton->setIcon(QIcon(QString("./res/icon/minusIcon.png")));

    // 创建QMenu
    QMenu *addToolButtonMenu = new QMenu(ui->addToolButton);

    // 添加动作到QMenu
    QAction *addDirectionLight = new QAction("directional light", addToolButtonMenu);
    QAction *addPointLight = new QAction("point light", addToolButtonMenu);
    QAction *addSpotLight = new QAction("spot light", addToolButtonMenu);
    addToolButtonMenu->addAction(addDirectionLight);
    addToolButtonMenu->addAction(addPointLight);
    addToolButtonMenu->addAction(addSpotLight);

    // 设置QToolButton的属性以在点击时显示下拉菜单
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

void LightWidget::Clear()
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
    propMap.PropVec3.clear();
    propMap.PropFloat.clear();
}

void LightWidget::SetModel(QStandardItemModel *model, int selectedIndex, int lightNum)
{
    ui->lightListView->setModel(model);
    if (lightNum > 0)
    {
        // default: if not select, select 0
        if (selectedIndex == -1)
            selectedIndex = 0;
        QModelIndex currentIndex = model->index(selectedIndex, 0);
        ui->lightListView->setCurrentIndex(currentIndex);
    }
}
void LightWidget::AddFloat3(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, Light *&light, Vec3 *val, double minVal, double maxVal)
{
    Float3Widget *propWidget = new Float3Widget(mainPropName, prop1Name, prop2Name, prop3Name, minVal, maxVal, this);
    propWidget->SetProp(*val);
    propMap.PropVec3.insert(QString(mainPropName), propWidget);
    lightPropLayout->addWidget(propWidget);
    propWidget->BindData(val);
}

void LightWidget::AddFloat(QString &mainPropName, QString &prop1Name, Light *&light, double *val, double minVal, double maxVal)
{
    FloatWidget *propWidget = new FloatWidget(mainPropName, prop1Name, minVal, maxVal, this);
    propWidget->SetProp(*val);
    propMap.PropFloat.insert(QString(mainPropName), propWidget);
    lightPropLayout->addWidget(propWidget);
    propWidget->BindData(val);
}
