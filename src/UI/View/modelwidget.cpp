#include "modelwidget.h"
#include "ui_modelwidget.h"

ModelWidget::ModelWidget(QWidget *parent) : TabWidget(parent),
                                            ui(new Ui::ModelWidget)
{
    ui->setupUi(this);

    Clear();
    modelTransformPropLayout = new QVBoxLayout();
    modelTransformPropLayout->setAlignment(Qt::AlignTop);
    ui->transformPropWidget->setLayout(modelTransformPropLayout);

    modelMeshInfoLayout = new QVBoxLayout();
    modelMeshInfoLayout->setAlignment(Qt::AlignTop);
    ui->meshInfoPropWidget->setLayout(modelMeshInfoLayout);

    modelMaterialPropLayout = new QVBoxLayout();
    modelMaterialPropLayout->setAlignment(Qt::AlignTop);
    ui->materialPropWidget->setLayout(modelMaterialPropLayout);
}

ModelWidget::~ModelWidget()
{
    Clear();
    delete ui;
}

void ModelWidget::AddFloat3(QString &mainPropName, QString &prop1Name, QString &prop2Name, QString &prop3Name, Vec3 *val, double minVal, double maxVal, const QString &tag)
{
    Float3Widget *propWidget = new Float3Widget(mainPropName, prop1Name, prop2Name, prop3Name, minVal, maxVal, this);
    propWidget->SetProp(*val);
    propMap.PropVec3.insert(QString(mainPropName), propWidget);
    GetTargetVBoxLayout(tag)->addWidget(propWidget);
    propWidget->BindData(val);
}

QVBoxLayout *&ModelWidget::GetTargetVBoxLayout(const QString &tag)
{
    if (tag == "Transform")
        return modelTransformPropLayout;
    else if (tag == "MeshInfo")
        return modelMeshInfoLayout;
    else if (tag == "Material")
        return modelMaterialPropLayout;
    throw("wrong tag");
    return modelTransformPropLayout;
}

void ModelWidget::AddFloat(QString &mainPropName, QString &prop1Name, double *val, double minVal, double maxVal, const QString &tag)
{
    FloatWidget *propWidget = new FloatWidget(mainPropName, prop1Name, minVal, maxVal, this);
    propWidget->SetProp(*val);
    propMap.PropFloat.insert(QString(mainPropName), propWidget);
    GetTargetVBoxLayout(tag)->addWidget(propWidget);
    propWidget->BindData(val);
}

void ModelWidget::AddInt(QString &mainPropName, QString &prop1Name, int *val, int minVal, int maxVal, const QString &tag)
{
    FloatWidget *propWidget = new FloatWidget(mainPropName, prop1Name, minVal, maxVal, this);
    propWidget->SetProp(*val);
    propMap.PropFloat.insert(QString(mainPropName), propWidget);
    GetTargetVBoxLayout(tag)->addWidget(propWidget);
    propWidget->BindData(val);
}

void ModelWidget::AddColorImg3(QString &mainPropName, Vec4 *color, const QString &tag,
                               std::string *texturePath)
{
    ColorImgWidget *propWidget = new ColorImgWidget(mainPropName);
    propWidget->SetProp(*color);
    propMap.propColorTexture.insert(QString(mainPropName), propWidget);
    GetTargetVBoxLayout(tag)->addWidget(propWidget);
    propWidget->BindData(color, texturePath);
}

void ModelWidget::AddImagePanel(QString &mainPropName, const QString &tag, std::string *texturePath)
{
    ImagePanel *propWidget = new ImagePanel(mainPropName);
    propMap.propImage.insert(QString(mainPropName), propWidget);
    GetTargetVBoxLayout(tag)->addWidget(propWidget);
    propWidget->BindData(texturePath);
}

void ModelWidget::AddImageSlider(QString &mainPropName, float *factor, const QString &tag,
                                 std::string *texturePath)
{
    ImageSlider *propWidget = new ImageSlider(mainPropName);
    propWidget->SetProp(*factor);
    propMap.propImageFactor.insert(QString(mainPropName), propWidget);
    GetTargetVBoxLayout(tag)->addWidget(propWidget);
    propWidget->BindData(factor, texturePath);
}