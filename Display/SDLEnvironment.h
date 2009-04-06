//
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SDL_ENVIRONMENT_H_
#define _OE_SDL_ENVIRONMENT_H_

#include <Display/IEnvironment.h>

#include <Display/SDLFrame.h>
#include <Devices/SDLInput.h>
namespace OpenEngine {
namespace Display {

/**
 * An environment for the SDL toolkit.
 *
 * @class SDLEnvironment SDLEnvironment.h Display/SDLEnvironment.h
 */
class SDLEnvironment : public IEnvironment {
private:

    SDLFrame* frame;
    Devices::SDLInput* input;

public:

    SDLEnvironment(int width = 640,
                   int height = 480, 
                   int depth = 32,
                   FrameOption options = FrameOption()) {
        frame = new SDLFrame(width, height, depth, options);
        input = new Devices::SDLInput();
    }

    void Handle(Core::InitializeEventArg arg) {
        frame->Handle(arg);
        input->Handle(arg);
    }
    void Handle(Core::ProcessEventArg arg) {
        frame->Handle(arg);
        input->Handle(arg);
    }
    void Handle(Core::DeinitializeEventArg arg) {
        frame->Handle(arg);
        input->Handle(arg);
    }

    IFrame&             GetFrame()    { return *frame; }
    Devices::IMouse*    GetMouse()    { return input; }
    Devices::IKeyboard* GetKeyboard() { return input; }
    Devices::IJoystick* GetJoystick() { return input; }

};

} // NS Display
} // NS OpenEngine

#endif // _OE_SDL_ENVIRONMENT_H_
