#include "ViewModel.h"

ViewModel::ViewModel()
{
}

void ViewModel::SetModel(std::shared_ptr<Config> config)
{
    m_config = config;
    m_newLightPropertyCommand = std::make_shared<NewLightPropertyCommand>(this);
    m_viewModelSink = std::make_shared<ViewModelSink>(this);
}

void ViewModel::Exec_newLightPropertyCommand(int lightIndex)
{
    m_config->NewLightProperty(lightIndex);
}

std::shared_ptr<ICommandBase> ViewModel::GetNewLightPropertyCommand()
{
    return std::static_pointer_cast<ICommandBase>(m_newLightPropertyCommand);
}
