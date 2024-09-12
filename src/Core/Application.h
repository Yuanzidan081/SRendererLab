#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include "Render/FrameBuffer.h"
#include "Render/CorePipeline.h"

class Application : public QObject
{
    Q_OBJECT
public:
    Application(int width, int height);
    ~Application();

    void Stop();

    int GetFps() { return m_fps; }
    void ResetFps() { m_fps = 0; }

    void Run();

signals:
    void frameReady(unsigned char *image);

    void frameReadyGbufferPos(float *position);
    void frameReadyGbufferColor(float *color);
    void frameReadyGbufferNormal(float *normal);

private:
    bool m_stopped;
    CorePipeline *m_pipeline;
    int m_fps;
    int m_width;
    int m_height;
};

#endif // APPLICATION_H