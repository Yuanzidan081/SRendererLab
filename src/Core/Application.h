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
    void Resize(int width, int height);
    ~Application();
    void Run();
    void Stop();
    int GetHeight() { return m_pipeline->GetWidth(); }
    int GetWidth() { return m_pipeline->GetHeight(); }

signals:
    void frameReady(unsigned char *image);

private:
    bool m_stopped;
    Pipeline *m_pipeline;
};

#endif // APPLICATION_H