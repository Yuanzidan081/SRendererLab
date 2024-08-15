#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "Render/FrameBuffer.h"
#include "Render/Pipeline.h"

class Application : public QObject
{
    Q_OBJECT
public:
    Application(int width, int height);
    ~Application();

    void Stop();

    int GetHeight() { return m_pipeline->GetWidth(); }
    int GetWidth() { return m_pipeline->GetHeight(); }
    int GetFps() { return m_fps; }
    void ResetFps() { m_fps = 0; }

    void Run();

    void OnReceiveKeyEvent(int key);
signals:
    void frameReady(unsigned char *image);

private:
    bool m_stopped;
    Pipeline *m_pipeline;
    int m_fps;
    int m_width;
    int m_height;
    /* QTimer *m_timer; */
};

#endif // APPLICATION_H