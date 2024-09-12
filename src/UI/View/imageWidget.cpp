#include "imageWidget.h"
#include "mainwidget.h"

#include <QPainter>
ImageWidget::ImageWidget(QWidget *parent) : m_canvas(nullptr)
{
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

void ImageWidget::reveiveFramePos(float *image)
{
    if (m_canvas)
        delete m_canvas;
    m_canvas = new QImage(screenWidth, screenHeight, QImage::Format_RGB888);
    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++)
        {
            //             m_ColorBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(255.0f * Clamp(color.r, 0.0f, 1.0f));
            // m_ColorBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(255.0f * Clamp(color.g, 0.0f, 1.0f));
            // m_ColorBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(255.0f * Clamp(color.b, 0.0f, 1.0f));
            QRgb pixel = qRgb(static_cast<unsigned char>(255.0f * Clamp(image[3 * (y * screenWidth + x) + 0], 0.0f, 1.0f)),
                              static_cast<unsigned char>(255.0f * Clamp(image[3 * (y * screenWidth + x) + 1], 0.0f, 1.0f)),
                              static_cast<unsigned char>(255.0f * Clamp(image[3 * (y * screenWidth + x) + 2], 0.0f, 1.0f)));
            m_canvas->setPixel(x, y, pixel);
        }
    }

    // m_canvas = new QImage(image, screenWidth, screenHeight, QImage::Format_RGB888);

    update();
}

void ImageWidget::reveiveFrameColor(float *image)
{

    if (m_canvas)
        delete m_canvas;
    m_canvas = new QImage(screenWidth, screenHeight, QImage::Format_RGBA8888);
    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++)
        {
            Vec4 color = Vec4(image[4 * (y * screenWidth + x) + 0], image[4 * (y * screenWidth + x) + 1],
                              image[4 * (y * screenWidth + x) + 2], image[4 * (y * screenWidth + x) + 3]);
            QRgb pixel = qRgba(static_cast<unsigned char>(255.0f * Clamp(image[4 * (y * screenWidth + x) + 0], 0.0f, 1.0f)),
                               static_cast<unsigned char>(255.0f * Clamp(image[4 * (y * screenWidth + x) + 1], 0.0f, 1.0f)),
                               static_cast<unsigned char>(255.0f * Clamp(image[4 * (y * screenWidth + x) + 2], 0.0f, 1.0f)),
                               static_cast<unsigned char>(255.0f * Clamp(image[4 * (y * screenWidth + x) + 3], 0.0f, 1.0f)));
            m_canvas->setPixel(x, y, pixel);
        }
    }

    // m_canvas = new QImage(image, screenWidth, screenHeight, QImage::Format_RGB888);

    update();
}

void ImageWidget::reveiveFrameNormal(float *image)
{
    if (m_canvas)
        delete m_canvas;
    m_canvas = new QImage(screenWidth, screenHeight, QImage::Format_RGB888);
    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++)
        {
            //             m_ColorBuffer[ind * m_Channels + 0] = static_cast<unsigned char>(255.0f * Clamp(color.r, 0.0f, 1.0f));
            // m_ColorBuffer[ind * m_Channels + 1] = static_cast<unsigned char>(255.0f * Clamp(color.g, 0.0f, 1.0f));
            // m_ColorBuffer[ind * m_Channels + 2] = static_cast<unsigned char>(255.0f * Clamp(color.b, 0.0f, 1.0f));
            QRgb pixel = qRgb(static_cast<unsigned char>(255.0f * Clamp(image[3 * (y * screenWidth + x) + 0], 0.0f, 1.0f)),
                              static_cast<unsigned char>(255.0f * Clamp(image[3 * (y * screenWidth + x) + 1], 0.0f, 1.0f)),
                              static_cast<unsigned char>(255.0f * Clamp(image[3 * (y * screenWidth + x) + 2], 0.0f, 1.0f)));
            m_canvas->setPixel(x, y, pixel);
        }
    }

    // m_canvas = new QImage(image, screenWidth, screenHeight, QImage::Format_RGB888);

    update();
}
