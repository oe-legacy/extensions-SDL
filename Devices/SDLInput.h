// Header file for the SDL implementation of IMouse and IKeyboard.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SDL_INPUT_MODULE_H_
#define _SDL_INPUT_MODULE_H_

// Cross platform SDL header
#include <Meta/SDL.h>

// OpenEngine input device interfaces
#include <Devices/IMouse.h>
#include <Devices/IKeyboard.h>
#include <Devices/IJoystick.h>
#include <Core/Event.h>
#include <Core/IModule.h>

namespace OpenEngine {
namespace Devices {

/**
 * SDL implementation of IMouse and IKeyboard.
 *
 * Implementation and method documentation is in the SDLInput.cpp
 * file. Additional documentation is in the interface files IMouse.h
 * and IKeyboard.h
 */
class SDLInput
    : public IKeyboard
    , public IMouse
    , public IJoystick
    , public Core::IModule {

protected:

    MouseState       state;

    JoystickState joystickState;

    bool haveJoystick;
    SDL_Joystick *firstJoystick;

    Core::Event<KeyboardEventArg>       keyEvent;
    Core::Event<MouseMovedEventArg>     mouseMovedEvent;
    Core::Event<MouseButtonEventArg>    mouseButtonEvent;
    Core::Event<JoystickButtonEventArg> joystickButtonEvent;
    Core::Event<JoystickAxisEventArg>   joystickAxisEvent;
    
public:

    SDLInput();
    ~SDLInput();

    // IModule methods
    void Handle(Core::InitializeEventArg arg);
    void Handle(Core::ProcessEventArg arg);
    void Handle(Core::DeinitializeEventArg arg);

    // Event lists
    Core::IEvent<KeyboardEventArg>&       KeyEvent();
    Core::IEvent<MouseMovedEventArg>&     MouseMovedEvent();
    Core::IEvent<MouseButtonEventArg>&    MouseButtonEvent();
    Core::IEvent<JoystickButtonEventArg>& JoystickButtonEvent();
    Core::IEvent<JoystickAxisEventArg>&	  JoystickAxisEvent();

    // IMouse methods
    void HideCursor();
    void ShowCursor();
    void SetCursor(int x, int y);
    MouseState GetState();

};

} // NS Devices
} // NS OpenEngine

#endif // _SDL_INPUT_MODULE_H_
