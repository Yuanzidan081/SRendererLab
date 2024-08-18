#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include "Core/Application.h"
#include "Core/Base.h"
#include <QKeyEvent>
#include "Core/KeyCode.h"
MainWidget::MainWidget(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MainWidget), itemMdl(nullptr)

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
    m_app->moveToThread(m_appThread);

    // https://blog.debao.me/2013/08/how-to-use-qthread-in-the-right-way-part-1/
    connect(m_timer, &QTimer::timeout, this, &MainWidget::DisplayFps);
    connect(m_app, &Application::frameReady, ui->imageWidget, &ImageWidget::reveiveFrame);
    this->setWindowTitle("SRendererLab");
    m_timer->start(1000);
    m_appThread->start();

    m_inputTimer = new QTimer(this);
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

void MainWidget::DisplayTreeNode()
{
    if (itemMdl)
        delete itemMdl;
    itemMdl = new QStandardItemModel(this);
    for (size_t i = 0; i < m_config->m_models.size(); ++i)
    {
        QString mdl = static_cast<QString>(m_config->m_models[i]->m_name.c_str());
        QStandardItem *mdlItem = new QStandardItem(mdl);
        itemMdl->appendRow(mdlItem);
        for (int j = 0; j < m_config->m_models[i]->m_objectNum; j++)
        {
            QString obj = static_cast<QString>(("    " + m_config->m_models[i]->m_objects[j].m_mesh->m_name).c_str());
            QStandardItem *objItem = new QStandardItem(obj);
            itemMdl->appendRow(objItem);
        }
    }
    ui->listView->setModel(itemMdl);
}
