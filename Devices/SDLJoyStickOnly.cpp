#include "SDLJoystickOnly.h"

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Devices {

using Core::Event;
using Core::IEvent;
using Core::ProcessEventArg;
using Core::InitializeEventArg;
using Core::DeinitializeEventArg;

SDLJoystickOnly::SDLJoystickOnly() : IJoystick() {

    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);


    firstStick = SDL_JoystickOpen(0);


}

SDLJoystickOnly::~SDLJoystickOnly() {

}

void SDLJoystickOnly::Handle(ProcessEventArg arg) {
    
    if (!firstStick) return;

    SDL_JoystickUpdate();


    JoystickAxisEventArg jarg;
    
    

    for (int i = 0; i < SDL_JoystickNumAxes(firstStick); i++) {
        jarg.axis = i;
        jarg.value = SDL_JoystickGetAxis(firstStick, i);
        jarg.state.axisState[i] = jarg.value;
    
        //logger.info << "axis " << i << " " << jarg.value << logger.end;
    }
    joystickAxisEvent.Notify(jarg);

}
void SDLJoystickOnly::Handle(InitializeEventArg arg) {

}
void SDLJoystickOnly::Handle(DeinitializeEventArg arg) {

}

IEvent<JoystickButtonEventArg>& SDLJoystickOnly::JoystickButtonEvent() {
    return this->joystickButtonEvent;
}

IEvent<JoystickAxisEventArg>& SDLJoystickOnly::JoystickAxisEvent() {
    return this->joystickAxisEvent;
}


}
}
