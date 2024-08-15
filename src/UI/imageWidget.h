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
#include <memory>
#include <QMouseEvent>
class MainWidget;
class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget *parent = nullptr);
    ~ImageWidget();

    // void updateFrame();
    void paintEvent(QPaintEvent *event) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void reveiveFrame(unsigned char *image);

private:
    QImage *m_canvas;
};

#endif // IMAGEWIDGHT_H