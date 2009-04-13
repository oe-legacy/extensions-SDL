#ifndef _SDL_JOYSTICK_ONLY_H_
#define _SDL_JOYSTICK_ONLY_H_


#include <Meta/SDL.h>

#include <Devices/IJoystick.h>
#include <Core/Event.h>
#include <Core/IModule.h>

namespace OpenEngine {
namespace Devices {

class SDLJoystickOnly
    : public IJoystick
    , public Core::IModule {
            

    Core::Event<JoystickButtonEventArg> joystickButtonEvent;
    Core::Event<JoystickAxisEventArg>   joystickAxisEvent;

    SDL_Joystick* firstStick;


public: 
    SDLJoystickOnly();
    ~SDLJoystickOnly();

    void Handle(Core::InitializeEventArg arg);
    void Handle(Core::ProcessEventArg arg);
    void Handle(Core::DeinitializeEventArg arg);
    
    Core::IEvent<JoystickButtonEventArg>& JoystickButtonEvent();
    Core::IEvent<JoystickAxisEventArg>& JoystickAxisEvent();

    };

}
}


#endif
