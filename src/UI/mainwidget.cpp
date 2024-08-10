#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include "Core/Application.h"
#include "Core/Base.h"
#include <QKeyEvent>
#include "Core/KeyCode.h"
MainWidget::MainWidget(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MainWidget)

{
    ui->setupUi(this);
    // 设置窗口标志，禁止缩放
    setFocusPolicy(Qt::StrongFocus);
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    m_timer = new QTimer(this);
    m_app = new Application(screenWidth, screenHeight);
    m_appThread = new QThread(this);

    connect(m_appThread, &QThread::started, m_app, &Application::Run);
    connect(m_appThread, &QThread::finished, m_app, &QObject::deleteLater);
    m_app->moveToThread(m_appThread);

    // https://blog.debao.me/2013/08/how-to-use-qthread-in-the-right-way-part-1/
    connect(m_timer, &QTimer::timeout, this, &MainWidget::DisplayFps);
    connect(m_app, &Application::frameReady, ui->imageWidget, &ImageWidget::reveiveFrame);

    m_timer->start(1000);
    m_appThread->start();
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
    this->setWindowTitle("SRendererLab" + QString(" fps: %1 ")
                                              .arg(fps));
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    // std::cout << key << std::endl;
    switch (key)
    {
    case SKey_W:
    case SKey_S:
    case SKey_D:
    case SKey_A:
    case SKey_Q:
    case SKey_E:
    case SKey_Down:
    case SKey_Up:
    case SKey_Left:
    case SKey_Right:

        m_app->OnReceiveKeyEvent(key);
        break;
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
}
