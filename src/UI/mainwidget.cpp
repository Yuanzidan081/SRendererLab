#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include "Core/Application.h"
#include "Core/Base.h"
MainWidget::MainWidget(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MainWidget)

{
    ui->setupUi(this);
    // 设置窗口标志，禁止缩放
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    connect(ui->horizontalSlider, &QSlider::sliderReleased, this, [&]()
            { Application::s_cameraZ = ui->horizontalSlider->value(); });
    m_timer = new QTimer(this);
    m_app = new Application(screenWidth, screenHeight);
    m_appThread = new QThread(this);

    connect(m_appThread, &QThread::started, m_app, &Application::Run);
    // https://blog.debao.me/2013/08/how-to-use-qthread-in-the-right-way-part-1/
    connect(m_timer, &QTimer::timeout, this, [&]()
            {int fps = m_app->GetFps();
    m_app->ResetFps();
    DisplayFps(fps); });
    connect(m_app, &Application::frameReady, ui->image, &ImageLabel::reveiveFrame);
    connect(m_app, &Application::fpsReady, this, &MainWidget::DisplayFps);
    connect(m_appThread, &QThread::finished, m_app, &QObject::deleteLater);

    m_app->moveToThread(m_appThread);
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

void MainWidget::DisplayFps(int fps)
{
    // std::cout << fps << std::endl;
    ui->groupBoxWindow->setTitle(QString("fps: %1").arg(fps));
}
