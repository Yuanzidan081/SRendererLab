#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include "Render/FrameBuffer.h"
#include "Render/Pipeline.h"
class Application : public QObject
{
    Q_OBJECT
public:
    Application(int width, int height);
    ~Application();
    void Run();
    void Stop();
    int GetHeight() { return m_pipeline->GetWidth(); }
    int GetWidth() { return m_pipeline->GetHeight(); }
    int GetFps() { return m_fps; }
    void ResetFps() { m_fps = 0; }
    static float s_cameraZ;

signals:
    void frameReady(unsigned char *image);

private:
    bool m_stopped;
    Pipeline *m_pipeline;
    int m_fps;
};

#endif // APPLICATION_H