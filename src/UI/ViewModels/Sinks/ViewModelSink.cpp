#include "VIewModelSink.h"
#include "Ui/ViewModels/ViewModel.h"
ViewModelSink::ViewModelSink(ViewModel *viewModelPtr)
{
    m_viewModelPtr = viewModelPtr;
}

void ViewModelSink::OnPropertyChanged(const std::string &str)
{
    m_viewModelPtr->Fire_OnPropertyChanged(str);
}
