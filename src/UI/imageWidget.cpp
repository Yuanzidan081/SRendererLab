#include "imageWidget.h"
#include "mainwidget.h"

#include <QPainter>
ImageWidget::ImageWidget(QWidget *parent) : m_canvas(nullptr)
{
    // 设置控件的焦点策略为 StrongFocus
    setFocusPolicy(Qt::StrongFocus);
}
ImageWidget::~ImageWidget()
{
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    if (m_canvas)
    {
        QPainter painter(this);
        painter.drawImage(0, 0, *m_canvas);
    }
    QWidget::paintEvent(event);
}

void ImageWidget::reveiveFrame(unsigned char *image)
{

    if (m_canvas)
        delete m_canvas;

    m_canvas = new QImage(image, screenWidth, screenHeight, QImage::Format_RGBA8888);

    update();
}
