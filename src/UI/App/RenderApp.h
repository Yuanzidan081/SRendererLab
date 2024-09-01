#ifndef RENDERAPP_H
#define RENDERAPP_H
#include "Core/Config.h"
#include "UI/ViewModels/ViewModel.h"
#include "UI/View/mainwidget.h"
// #include "../WINDOW/gamewindow.h"
// #include "../WINDOW/startpage.h"
// #include "../WINDOW/form.h"
// #include "../WINDOW/levelpage.h"
// #include "../WINDOW/teamview.h"
// #include "commands/startbuttoncommand.h"
// #include "commands/gamewindowcommand.h"
// #include "commands/gamecompletecommand.h"
// #include "commands/gameagaincommand.h"
// #include "commands/teamviewcommand.h"
// #include "commands/returnstartpagecommand.h"

class RenderApp
{
private:
    // startpage _startpageWindow;
    // Form _formWindow;
    // levelPage _levelPageWindow;
    // gamewindow _gameWindow;
    MainWidget m_mainWidget;
    // TeamView _teamViewWindow;
    std::shared_ptr<Config> m_model;
    std::shared_ptr<ViewModel> m_viewmodel;
    // std::shared_ptr<gameAgainCommand> _spGameAgainCommand;
    // std::shared_ptr<gamecompletecommand> _spGameCompleteCommand;
    // std::shared_ptr<StartButtonCommand> _spStartButtonCommand;
    // std::shared_ptr<gameWindowCommand> _spGameWindowCommand;
    // std::shared_ptr<teamViewCommand> _spTeamViewCommand;
    // std::shared_ptr<returnStartPageCommand> _spReturnStartPageCommand;

public:
    RenderApp() = default;
    ~RenderApp() = default;
    void Run();
    MainWidget *getMainWidget();
};
#endif // RENDERAPP_H