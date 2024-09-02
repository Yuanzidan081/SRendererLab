#ifndef NEW_LIGHT_PROPERTY_COMMAND_H
#define NEW_LIGHT_PROPERTY_COMMAND_H
#include "UI/Common/CommandBase.h"

class ViewModel;
class NewLightPropertyCommand : public ICommandBase
{
public:
    NewLightPropertyCommand(ViewModel *viewModel);

    virtual void SetParameter(const _new_any_space_::any &param);
    virtual void Exec();

private:
    int m_lightIndex;
    ViewModel *m_viewModel;
};
#endif // NEW_LIGHT_PROPERTY_COMMAND_H