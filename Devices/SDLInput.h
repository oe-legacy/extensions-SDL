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

namespace OpenEngine {
namespace Devices {

using OpenEngine::Core::Event;
using OpenEngine::Core::InitializeEventArg;
using OpenEngine::Core::ProcessEventArg;
using OpenEngine::Core::DeinitializeEventArg;

/**
 * SDL implementation of IMouse and IKeyboard.
 *
 * Implementation and method documentation is in the SDLInput.cpp
 * file. Additional documentation is in the interface files IMouse.h
 * and IKeyboard.h
 */
class SDLInput : public IKeyboard, public IMouse, public IJoystick {

protected:

    MouseState       state;

    JoystickState joystickState;

    bool haveJoystick;
    SDL_Joystick *firstJoystick;

    Event<KeyboardEventArg>    keyEvent;
    Event<MouseMovedEventArg>  mouseMovedEvent;
    Event<MouseButtonEventArg> mouseButtonEvent;
    Event<JoystickButtonEventArg> joystickButtonEvent;
    Event<JoystickAxisEventArg> joystickAxisEvent;

public:

    SDLInput();
    ~SDLInput();

    // IModule methods
    void Handle(InitializeEventArg arg);
    void Handle(ProcessEventArg arg);
    void Handle(DeinitializeEventArg arg);

    // Event lists
    IEvent<KeyboardEventArg>&		KeyEvent();
    IEvent<MouseMovedEventArg>&		MouseMovedEvent();
    IEvent<MouseButtonEventArg>&	MouseButtonEvent();
    IEvent<JoystickButtonEventArg>&	JoystickButtonEvent();
    IEvent<JoystickAxisEventArg>&	JoystickAxisEvent();

    // IMouse methods
    void HideCursor();
    void ShowCursor();
    void SetCursor(int x, int y);
    MouseState GetState();

};

} // NS Devices
} // NS OpenEngine

#endif // _SDL_INPUT_MODULE_H_
