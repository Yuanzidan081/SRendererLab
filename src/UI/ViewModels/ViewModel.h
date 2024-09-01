#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include "Commands/Command.h"
#include "Core/Config.h"
// #include "sinks/swviewmodelsink.h"
// #include "commands/layoutcommand.h"
// #include "commands/mousemovecommand.h"

class ViewModel : public Proxy_PropertyNotification<ViewModel>,
                  public Proxy_CommandNotification<ViewModel>
{
public:
    ViewModel();
    ~ViewModel() {}
    void SetModel(std::shared_ptr<Config> Model);
    // std::shared_ptr<SWMatrix> getSWMatrix();
    // std::shared_ptr<ICommandBase> getLayoutCommand();
    // std::shared_ptr<ICommandBase> getMouseMoveCommand();
    // void Exec_layout_command(int level);
    // void Exec_mouseMove_command(int row, int col);

private:
    std::shared_ptr<Config> m_config;
    // std::shared_ptr<SWViewModelSink> sp_SWViewModelSink_;
    // std::shared_ptr<layoutCommand> sp_layoutCommand_;
    // std::shared_ptr<mouseMoveCommand> sp_mouseMoveCommand_;
};

#endif // VIEWMODEL_H