#include "ViewModel.h"

ViewModel::ViewModel()
{
}

void ViewModel::SetModel(std::shared_ptr<Config> model)
{
    m_config = model;
}
