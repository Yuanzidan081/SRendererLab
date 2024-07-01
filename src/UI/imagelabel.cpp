#include "imagelabel.h"

ImageLabel *ImageLabel::m_window = nullptr;
ImageLabel::ImageLabel(QWidget *parent) : m_canvas(nullptr)
{

    m_window = this;
}

ImageLabel::~ImageLabel()
{
}

void ImageLabel::updateFrame()
{
    if (m_canvas)
    {
        this->setPixmap(QPixmap::fromImage(*m_canvas));
    }
}

void ImageLabel::reveiveFrame(unsigned char *image)
{

    if (m_canvas)
        delete m_canvas;

    m_canvas = new QImage(image, screenWidth, screenHeight, QImage::Format_RGBA8888);

    updateFrame();
}
