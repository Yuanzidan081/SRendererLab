#ifndef VIEW_MODEL_SINK_H
#define VIEW_MODEL_SINK_H
#include "UI/Common/CommandBase.h"
class ViewModel;
class ViewModelSink : public IPropertyNotification
{
public:
    ViewModelSink(ViewModel *viewModelPtr);
    virtual void OnPropertyChanged(const std::string &str);

private:
    ViewModel *m_viewModelPtr;
};

#endif // VIEW_MODEL_SINK_H