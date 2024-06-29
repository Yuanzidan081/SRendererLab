#include "window.h"
#include "ui_window.h"
#include <QPainter>
#include <QDebug>

int Window::window_Width = 400;
int Window::window_Height = 300;
Window *Window::m_window = nullptr;
Window::Window(QWidget *parent) : QWidget(parent),
                                  ui(new Ui::Window),
                                  m_canvas(nullptr)
{
    ui->setupUi(this);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Window::WinodwFpsUpdate);

    m_app = new Application(width(), height());
    window_Width = width();
    window_Height = height();
    m_window = this;
    m_appThread = new QThread(this);

    m_app->moveToThread(m_appThread);
    connect(m_appThread, &QThread::started, m_app, &Application::Run);
    connect(m_app, &Application::frameReady, this, &Window::reveiveFrame);
    connect(m_appThread, &QThread::finished, m_app, &QObject::deleteLater); // 线程结束以后将线程里的程序删除

    m_appThread->start();
    timer->start(1000);
}

Window::~Window()
{
    delete ui;
    m_app->Stop();

    m_appThread->quit();
    m_appThread->wait();
    if (m_canvas)
        delete m_canvas;
    if (m_appThread)
        delete m_appThread;
    m_app = nullptr;
    m_appThread = nullptr;
    m_canvas = nullptr;
}

void Window::paintEvent(QPaintEvent *event)
{

    if (m_canvas)
    {
        QPainter painter(this);
        painter.drawImage(0, 0, *m_canvas);
    }
    QWidget::paintEvent(event);
}

void Window::reveiveFrame(unsigned char *image)
{
    if (window_Height != width() || window_Width != width())
    {
        window_Width = width();
        window_Height = height();
    }
    if (m_canvas)
        delete m_canvas;
    m_canvas = new QImage(image, width(), height(), QImage::Format_RGBA8888);
    // m_canvas = new QImage(image, width(), height(), QImage::Format_RGB888);
    //  qDebug() << width() << " " << height();
    repaint();
}

void Window::WinodwFpsUpdate()
{
    int fps = m_app->GetFps();
    m_app->ResetFps();
    emit fpsUpdate(fps);
}
