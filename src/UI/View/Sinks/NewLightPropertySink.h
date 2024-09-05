#ifndef NEW_LIGHT_PROPERTY_SINK_H
#define NEW_LIGHT_PROPERTY_SINK_H
#include "UI/Common/CommandBase.h"
class MainWidget;
class NewLightPropertySink : public IPropertyNotification
{
public:
    NewLightPropertySink(MainWidget *ptr);
    virtual void OnPropertyChanged(const std::string &str);

private:
    MainWidget *m_mainWidget;
};

#endif // NEW_LIGHT_PROPERTY_SINK_H