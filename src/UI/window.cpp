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

    m_app = new Application(width(), height());
    window_Width = width();
    window_Height = height();
    m_window = this;
    m_appThread = new QThread;

    m_app->moveToThread(m_appThread);
    connect(m_appThread, &QThread::started, m_app, &Application::Run);
    connect(m_app, &Application::frameReady, this, &Window::reveiveFrame);
    connect(m_appThread, &QThread::finished, m_app, &QObject::deleteLater); // 线程结束以后将线程里的程序删除

    m_appThread->start();
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
        // painter.setPen(Qt::gray);
        // painter.setBrush(Qt::green);
        // qDebug() << m_canvas[0];
        // painter.drawRect(0, 0, width(), height());
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
    // qDebug() << width() << " " << height();
    repaint();
}

void Window::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    emit windowResized();
}

void Window::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit windowResized();
}