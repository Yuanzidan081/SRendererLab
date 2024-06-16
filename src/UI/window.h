#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QThread>

#include "Core/Base.h"
#include "Core/Application.h"
#include <QTimer>
namespace Ui
{
    class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();
    void paintEvent(QPaintEvent *event) override;
    void reveiveFrame(unsigned char *image);
    void WinodwFpsUpdate();
    static int window_Width, window_Height;
    static Window *m_window;
signals:
    void fpsUpdate(int fps);

private:
    Ui::Window *ui;
    QImage *m_canvas;

    Application *m_app;
    QThread *m_appThread;
    QTimer *timer;
};

#endif // WINDOW_H
