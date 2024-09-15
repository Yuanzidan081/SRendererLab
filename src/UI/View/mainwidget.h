#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
// #include "window.h"
#include "imageWidget.h"
#include "lightWidget.h"
#include "modelWidget.h"
#include "configwidget.h"
#include "Core/RenderLoop.h"
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
    explicit MainWidget(std::shared_ptr<Light> &light, QWidget *parent = nullptr);
    ~MainWidget();
    void DisplayFps();

    // Set up
    void SetUpModelTabWidget();
    void SetUpLightTabWidget();
    void SetUpConfigTabWidget();

    void DealInput();

    void UpdateSelectedLightProperty();
    void UpdateSelectedModelProperty();

    // response to mouse click
    void OnChangeSelectedModel(int index);
    void OnChangeSelectedLight(int index);

    // void OnChange

    // set command
    void SetNewLightPropertyCommand(std::shared_ptr<ICommandBase> command);

protected:
    // system callbacks
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event);

public slots:
    void UpdateLightWidget();
    void UpdateModelHierachyListView();

private:
    Ui::MainWidget *ui;

    RenderLoop *m_app;
    QThread *m_appThread;
    QThread *m_loadAssetThread;
    QTimer *m_timer;
    std::shared_ptr<Config> m_config;
    QStandardItemModel *m_itemMdl;
    QStandardItemModel *m_itemLight;

    int m_selectedLightIndex;
    int m_selectedModelIndex;
    int m_selectedMeshIndex;

    // UI pointer
    LightWidget *lightWidget;
    ModelWidget *modelWidget;
    ConfigWidget *configWidget;

    // mouseMove
    bool m_firstMouseMove;
    QPoint m_preMousePos;
    float m_rotateSpeed = 0.1f;
    float m_scaleSpeed = 0.01f;
    float m_deltaX, m_deltaY;

    // mousePress and mouseRelease
    QTimer *m_inputTimer;
    QVector<Qt::Key> m_pressedKeys;

    // command
    std::shared_ptr<ICommandBase> m_newLightPropertyCommand;

    std::shared_ptr<Light> &m_currentLight;
};
#endif // MAINWIDGET_H
