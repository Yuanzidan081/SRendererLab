#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include "Core/Application.h"
#include "Core/Base.h"
#include <QKeyEvent>
#include "Core/KeyCode.h"
MainWidget::MainWidget(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MainWidget), m_itemMdl(nullptr), m_itemLight(nullptr),
                                          m_selectedLightIndex(0), m_lightNum(0)

{
    m_config = Config::GetInstance();
    ui->setupUi(this);

    // 设置窗口标志，禁止缩放
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    this->setMouseTracking(true);
    ui->imageWidget->setMouseTracking(true);
    ui->imageWidget->installEventFilter(this);
    m_timer = new QTimer(this);
    m_app = new Application(screenWidth, screenHeight);
    m_appThread = new QThread(this);

    connect(m_appThread, &QThread::started, m_app, &Application::Run);
    connect(m_appThread, &QThread::finished, m_app, &QObject::deleteLater);
    connect(m_config, &Config::TreeNodeChanged, this, &MainWidget::DisplayTreeNode);
    connect(m_config, &Config::LightChanged, this, &MainWidget::UpdateLightProp);

    m_app->moveToThread(m_appThread);

    // https://blog.debao.me/2013/08/how-to-use-qthread-in-the-right-way-part-1/
    connect(m_timer, &QTimer::timeout, this, &MainWidget::DisplayFps);
    connect(m_app, &Application::frameReady, ui->imageWidget, &ImageWidget::reveiveFrame);
    this->setWindowTitle("SRendererLab");
    m_timer->start(1000);
    m_appThread->start();

    m_inputTimer = new QTimer(this);
    SetUpLightTabWidget();
}

MainWidget::~MainWidget()
{
    delete ui;
    m_app->Stop();

    m_appThread->quit();
    m_appThread->wait();

    if (m_appThread)
        delete m_appThread;
    m_app = nullptr;
    m_appThread = nullptr;
}

void MainWidget::DisplayFps()
{
    int fps = m_app->GetFps();
    m_app->ResetFps();
    ui->textEdit->clear();
    ui->textEdit->append(QString(" fps: %1 ").arg(fps));
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    m_pressedKeys.append(static_cast<Qt::Key>(event->key()));
    if (!m_inputTimer->isActive())
    {
        m_inputTimer->start(100);
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (m_inputTimer->isActive() && !m_pressedKeys.isEmpty())
    {
        m_inputTimer->stop();
        DealInput();
    }
    m_pressedKeys.removeAll(static_cast<Qt::Key>(event->key()));
}

void MainWidget::DealInput()
{
    if (m_pressedKeys.contains(Qt::Key_W))
    {
        m_config->m_fpsCamera->MoveForward(-0.2);
    }
    if (m_pressedKeys.contains(Qt::Key_S))
    {
        m_config->m_fpsCamera->MoveForward(0.2);
    }
    if (m_pressedKeys.contains(Qt::Key_A))
    {
        m_config->m_fpsCamera->MoveRight(-0.2);
    }
    if (m_pressedKeys.contains(Qt::Key_D))
    {
        m_config->m_fpsCamera->MoveRight(0.2);
    }
    if (m_pressedKeys.contains(Qt::Key_Q))
    {
        m_config->m_fpsCamera->MoveUp(0.2);
    }
    if (m_pressedKeys.contains(Qt::Key_E))
    {
        m_config->m_fpsCamera->MoveUp(-0.2);
    }
}

bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->imageWidget)
    {
        if (event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (!(mouseEvent->buttons() & Qt::LeftButton))
                m_firstMouseMove = true;
            if (m_firstMouseMove)
            {
                m_firstMouseMove = false;
                m_preMousePos = mouseEvent->pos();
            }
            else
            {
                QPoint delta = mouseEvent->pos() - m_preMousePos;
                m_preMousePos = mouseEvent->pos();
                if (mouseEvent->buttons() & Qt::LeftButton)
                {
                    m_deltaX = m_rotateSpeed * delta.x();
                    m_deltaY = m_rotateSpeed * delta.y();
                    m_config->m_fpsCamera->RotateYaw(-m_deltaX);
                    m_config->m_fpsCamera->RotatePitch(-m_deltaY);
                }
            }
        }
        else if (event->type() == QEvent::Wheel)
        {
            QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
            float delta = m_scaleSpeed * wheelEvent->delta();
            // std::cout << delta << std::endl;
            m_config->m_fpsCamera->Zoom(-delta);
        }
    }
    return QWidget::eventFilter(watched, event);
}

void MainWidget::SetUpLightTabWidget()
{

    QWidget *lightWidgetPage = new QWidget();

    QVBoxLayout *lightWidgetLayout = new QVBoxLayout(lightWidgetPage);
    lightWidget = new LightWidget();
    lightWidgetLayout->setContentsMargins(0, 0, 0, 0);
    lightWidgetLayout->addWidget(lightWidget);
    ui->propTabWidget->insertTab(0, lightWidgetPage, "Light");
}

void MainWidget::UpdateLightProp()
{
    if (m_itemLight)
        delete m_itemLight;
    m_itemLight = new QStandardItemModel(this);
    m_lightNum = m_config->m_lights.size();
    for (size_t i = 0; i < m_lightNum; ++i)
    {
        QString lightName = static_cast<QString>(m_config->m_lights[i]->m_name.c_str());
        QStandardItem *lightItem = new QStandardItem(lightName);
        m_itemLight->appendRow(lightItem);
    }
    if (m_lightNum == 0)
        m_selectedLightIndex = -1;
    lightWidget->SetModel(m_itemLight, m_selectedLightIndex, m_lightNum);
    if (m_selectedLightIndex != -1)
    {
        Light *&light = m_config->m_lights[m_selectedLightIndex];
        QString tag = static_cast<QString>(light->m_tag.c_str());
        if (tag == "Directional Light")
        {
            lightWidget->Clear();
            lightWidget->AddFloat3(QString("direction"), QString("x"), QString("y"), QString("z"), light, &(static_cast<DirectionalLight *>(light)->m_direction));
            lightWidget->AddFloat3(QString("ambient"), QString("x"), QString("y"), QString("z"), light, &(static_cast<DirectionalLight *>(light)->m_ambient), 0.0, 1.0);
            lightWidget->AddFloat3(QString("diffuse"), QString("x"), QString("y"), QString("z"), light, &(static_cast<DirectionalLight *>(light)->m_diffuse), 0.0, 1.0);
            lightWidget->AddFloat3(QString("specular"), QString("x"), QString("y"), QString("z"), light, &(static_cast<DirectionalLight *>(light)->m_specular), 0.0, 1.0);
        }
        else if (tag == "Point Light")
        {
            lightWidget->Clear();
            lightWidget->AddFloat3(QString("position"), QString("x"), QString("y"), QString("z"), light, &(static_cast<PointLight *>(light)->m_position));
            lightWidget->AddFloat3(QString("ambient"), QString("x"), QString("y"), QString("z"), light, &(static_cast<PointLight *>(light)->m_ambient), 0.0, 1.0);
            lightWidget->AddFloat3(QString("diffuse"), QString("x"), QString("y"), QString("z"), light, &(static_cast<PointLight *>(light)->m_diffuse), 0.0, 1.0);
            lightWidget->AddFloat3(QString("specular"), QString("x"), QString("y"), QString("z"), light, &(static_cast<PointLight *>(light)->m_specular), 0.0, 1.0);
            lightWidget->AddFloat3(QString("attenuation"), QString("x"), QString("y"), QString("z"), light, &(static_cast<PointLight *>(light)->m_attenuation), 0.0, 1.0);
        }
        else if (tag == "Spot Light")
        {
            lightWidget->Clear();
            lightWidget->AddFloat3(QString("position"), QString("x"), QString("y"), QString("z"), light, &(static_cast<SpotLight *>(light)->m_position));
            lightWidget->AddFloat3(QString("direction"), QString("x"), QString("y"), QString("z"), light, &(static_cast<SpotLight *>(light)->m_direction));
            lightWidget->AddFloat3(QString("ambient"), QString("x"), QString("y"), QString("z"), light, &(static_cast<SpotLight *>(light)->m_ambient), 0.0, 1.0);
            lightWidget->AddFloat3(QString("diffuse"), QString("x"), QString("y"), QString("z"), light, &(static_cast<SpotLight *>(light)->m_diffuse), 0.0, 1.0);
            lightWidget->AddFloat3(QString("specular"), QString("x"), QString("y"), QString("z"), light, &(static_cast<SpotLight *>(light)->m_specular), 0.0, 1.0);
            lightWidget->AddFloat3(QString("attenuation"), QString("x"), QString("y"), QString("z"), light, &(static_cast<SpotLight *>(light)->m_attenuation), 0.0, 1.0);
            lightWidget->AddFloat(QString("cutoff"), QString("x"), light, &(static_cast<SpotLight *>(light)->m_cutoff), 0.0, 1.0);
            lightWidget->AddFloat(QString("outCutoff"), QString("x"), light, &(static_cast<SpotLight *>(light)->m_outcutoff), 0.0, 1.0);
        }
    }
}

void MainWidget::DisplayTreeNode()
{
    if (m_itemMdl)
        delete m_itemMdl;
    m_itemMdl = new QStandardItemModel(this);
    for (size_t i = 0; i < m_config->m_models.size(); ++i)
    {
        QString mdl = static_cast<QString>(m_config->m_models[i]->m_name.c_str());
        QStandardItem *mdlItem = new QStandardItem(mdl);
        m_itemMdl->appendRow(mdlItem);
        if (m_config->m_models[i]->m_objectNum > 1)
        {
            for (int j = 0; j < m_config->m_models[i]->m_objectNum; j++)
            {
                QString obj = static_cast<QString>(("    " + m_config->m_models[i]->m_objects[j].m_mesh->m_name).c_str());
                QStandardItem *objItem = new QStandardItem(obj);
                m_itemMdl->appendRow(objItem);
            }
        }
    }
    ui->listView->setModel(m_itemMdl);
}
