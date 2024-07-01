#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QWidget>
#include <QThread>
#include <QPainter>
#include "Core/Base.h"
#include "Core/Application.h"
#include <QTimer>
#include <QPixmap>
class ImageLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ImageLabel(QWidget *parent = nullptr);
    ~ImageLabel();

    void updateFrame();

    /*     static int window_Width, window_Height; */
    static ImageLabel *m_window;

public slots:
    void reveiveFrame(unsigned char *image);

private:
    QImage *m_canvas;
};

#endif // IMAGEWIDGHT_H