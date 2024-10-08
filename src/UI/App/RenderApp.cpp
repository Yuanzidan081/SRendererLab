#include "RenderApp.h"

RenderApp::RenderApp() : m_config(Config::GetInstance()), m_mainWidget(m_config->GetCurrentLight())
{
}

void RenderApp::Run()
{
    m_viewModel = std::make_shared<ViewModel>();
    m_viewModel->SetModel(m_config); // 绑定viewmodel和model

    m_mainWidget.SetNewLightPropertyCommand(m_viewModel->GetNewLightPropertyCommand());

    // m_viewModel->AddPropertyNotification();

    // _gameWindow.setGameAgainCommand(viewmodel->getLayoutCommand());                  // 绑定gamewindow，打开一个新游戏窗口
    // _formWindow.setNewGameCommand(viewmodel->getLayoutCommand());                    // 绑定form弹窗，回到游戏窗口
    // _levelPageWindow.set_ptrCommand(viewmodel->getLayoutCommand());                  // 绑定levelpage
    // _gameWindow.set_ptrPointChangeTrackingCommand(viewmodel->getMouseMoveCommand()); // 从gamewindow获取鼠标移动事件，传入viewmodel
    // _gameWindow.set_Martix(viewmodel->getSWMatrix());                                // gamewindow得到matrix
    // _formWindow.setMartix(viewmodel->getSWMatrix()); // formwindow得到matrix

    // 接收器接收消息
    // m_viewModel->AddPropertyNotification(_gameWindow.getPtrWindowProSink());
    // m_viewModel->AddCommandNotification(_gameWindow.getPtrNewLayoutSink());
    // m_viewModel->AddCommandNotification(_gameWindow.getPtrPointChangeTrackingSink());
    // m_viewModel->AddPropertyNotification(_gameWindow.getPtrGameCompleteSink());

    // 智能指针赋值
    // _spStartButtonCommand = std::make_shared<StartButtonCommand>(this);
    // _spGameWindowCommand = std::make_shared<gameWindowCommand>(this);
    // _spGameCompleteCommand = std::make_shared<gamecompletecommand>(this);
    // _spGameAgainCommand = std::make_shared<gameAgainCommand>(this);
    // _spTeamViewCommand = std::make_shared<teamViewCommand>(this);
    // _spReturnStartPageCommand = std::make_shared<returnStartPageCommand>(this);

    // startpage的start button命令
    // _startpageWindow.set_ptrCommand(std::static_pointer_cast<ICommandBase>(this->_spStartButtonCommand));

    // startpage的team button命令
    // _startpageWindow.set_ptrTeamButtonCommand(std::static_pointer_cast<ICommandBase>(this->_spTeamViewCommand));

    // formwindow的menu button命令
    // _formWindow.setMenuCommand(std::static_pointer_cast<ICommandBase>(this->_spStartButtonCommand));

    // levelpage的关卡选择事件，打开一个游戏窗口
    // _levelPageWindow.set_ptrOpenCommand(std::static_pointer_cast<ICommandBase>(this->_spGameWindowCommand));

    // gamewindow完成一轮游戏后，触发form弹窗
    // _gameWindow.set_ptrGameCompleteCommand(std::static_pointer_cast<ICommandBase>(this->_spGameCompleteCommand));

    // formwindow选择重新开始游戏或继续下一关游戏时，打开游戏界面
    // _formWindow.setOpenCommand(std::static_pointer_cast<ICommandBase>(this->_spGameAgainCommand));

    // 退出teamviewwindow，回到startpage
    // _teamViewWindow.setStartPageCommand(std::static_pointer_cast<ICommandBase>(this->_spReturnStartPageCommand));

    // 运行时开启startpage
    m_mainWidget.show();
}
