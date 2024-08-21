#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
// #include "window.h"
#include "imageWidget.h"
#include "lightWidget.h"

#include "Core/Application.h"
#include "Core/Config.h"
#include <QStandardItemModel>
#include <QVector>
namespace Ui
{
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void DisplayFps();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void DealInput();
    bool eventFilter(QObject *watched, QEvent *event);

    void SetUpLightTabWidget();

public slots:
    void UpdateLightProp();
    void DisplayTreeNode();

private:
    Ui::MainWidget *ui;

    Application *m_app;
    QThread *m_appThread;
    QTimer *m_timer;
    Config *m_config;
    QStandardItemModel *m_itemMdl;
    QStandardItemModel *m_itemLight;
    int m_selectedLightIndex;
    int m_lightNum;
    // UI pointer
    LightWidget *lightWidget;

    // mouseMove
    bool m_firstMouseMove;
    QPoint m_preMousePos;
    float m_rotateSpeed = 0.1f;
    float m_scaleSpeed = 0.01f;
    float m_deltaX, m_deltaY;
    // mousePress and mouseRelease
    QTimer *m_inputTimer;
    QVector<Qt::Key> m_pressedKeys;
};
#endif // MAINWIDGET_H
