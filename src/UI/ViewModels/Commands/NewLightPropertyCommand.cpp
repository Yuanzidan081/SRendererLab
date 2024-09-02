#include "NewLightPropertyCommand.h"
#include "Render/Light.h"
#include <memory>
#include "UI/ViewModels/ViewModel.h"
NewLightPropertyCommand::NewLightPropertyCommand(ViewModel *viewModel)
{
    m_viewModel = viewModel;
}
void NewLightPropertyCommand::SetParameter(const _new_any_space_::any &param)
{
    m_lightIndex = _new_any_space_::any_cast<int>(param);
}

void NewLightPropertyCommand::Exec()
{
    m_viewModel->Exec_newLightPropertyCommand(m_lightIndex);
    // m_config->Exec_mouseMove_command(mouseOnRow,mouseOnCol);
    // m_config->Fire_OnCommandComplete("mouseMoveCommand", true);
}
