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
    int key = event->key();
    if (ui->imageWidget->hasFocus())
    {
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
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
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
            QString obj = static_cast<QString>(("    " + m_config->m_models[i]->m_objects[j].m_mesh.m_name).c_str());
            QStandardItem *objItem = new QStandardItem(obj);
            itemMdl->appendRow(objItem);
        }
    }
    ui->listView->setModel(itemMdl);
}
