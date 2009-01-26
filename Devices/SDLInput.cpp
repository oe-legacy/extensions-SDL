// Implementation file for the SDL implementation of IMouse and
// IKeyboard
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

// Module header
#include <Devices/SDLInput.h>

// OpenEngine key and button symbol definitions
#include <Devices/Symbols.h>

// OpenEngine logging library
#include <Logging/Logger.h>

#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Devices {

using OpenEngine::Core::Exception;

/**
 * Class constructor.
 */
SDLInput::SDLInput()
    : IKeyboard()
    , IMouse()
    , IJoystick()
    , haveJoystick(false)
{
    // initialize mouse state
    state.x = 0;
    state.y = 0;
    state.buttons = BUTTON_NONE;
}

/**
 * Class destructor.
 */
SDLInput::~SDLInput() {

}

/**
 * Module initialization method.
 * Called once on engine start up after all modules have been loaded.
 *
 * @see IModule::Initialize()
 */
void SDLInput::Handle(InitializeEventArg arg) {
    // Check that SDL has been initialized (SDLFrame does it)
    if (!SDL_WasInit(SDL_INIT_VIDEO))
        throw Exception("SDL video has not been initialized.");

    // Initialize for joysticks
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    haveJoystick = (SDL_NumJoysticks() > 0);
    if (haveJoystick) {
        SDL_JoystickEventState(SDL_ENABLE);
        firstJoystick = SDL_JoystickOpen(0);
        logger.info << "Found joystick: " << SDL_JoystickName(0) << logger.end;
        if (28 < SDL_JoystickNumAxes(firstJoystick))
            throw Exception("No support for joysticks with more then 28 axis.");
    }
}

/**
 * Module process method.
 * This is the main processing method of the module, called for every
 * module circulation.
 *
 * @see IModule::Process()
 */
void SDLInput::Handle(ProcessEventArg arg) {
    KeyboardEventArg karg;
    MouseMovedEventArg mmarg;
    SDL_Event event = {0};
    
    // Loop until there are no events left on the queue
    while(SDL_PollEvent(&event) && (SDL_GetAppState() & SDL_APPINPUTFOCUS )) {
        switch (event.type) {
        case SDL_QUIT:
            // @todo what do we wish to do here? 
            // OpenEngine::Core::IGameEngine::Instance().Stop();
            logger.info << "Recived SDL_QUIT" << logger.end;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            // set key symbol and modifier
            karg.sym = (Key)    event.key.keysym.sym;
            karg.mod = (KeyMod) event.key.keysym.mod;
            karg.type = (event.type == SDL_KEYDOWN) ? EVENT_PRESS : EVENT_RELEASE;
            // notify event
            keyEvent.Notify(karg);
            break;
        case SDL_MOUSEMOTION:
            // set mouse position and get button modifiers
            state.buttons = mmarg.buttons = (MouseButton)(int)SDL_GetMouseState(NULL, NULL);
            state.x = mmarg.x = event.motion.x;
            state.y = mmarg.y = event.motion.y;
            mmarg.dx = event.motion.xrel;
            mmarg.dy = event.motion.yrel;
            mouseMovedEvent.Notify(mmarg);
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
	    {
            // set mouse position and get button modifiers
            state.buttons = (MouseButton) (int) SDL_GetMouseState(NULL, NULL);
            state.x = event.button.x;
            state.y = event.button.y;
            // create a mouse event
            MouseButtonEventArg marg;
            marg.state = state;
            marg.button = (MouseButton) (int) SDL_BUTTON(event.button.button);
            marg.type = (event.type == SDL_MOUSEBUTTONDOWN) ? EVENT_PRESS : EVENT_RELEASE;
            mouseButtonEvent.Notify(marg);
            break;
	    }

	case SDL_JOYAXISMOTION:{
	    JoystickAxisEventArg jarg;
	    joystickState.axisState[event.jaxis.axis] = event.jaxis.value;
	    jarg.state = joystickState;
	    jarg.axis = event.jaxis.axis;
	    jarg.value = event.jaxis.value;
	    joystickAxisEvent.Notify(jarg);
	    break;
	}

	case SDL_JOYBUTTONDOWN:{
            JoystickButtonEventArg e;
            joystickState.buttons = (JoystickButton)(joystickState.buttons | 1<<event.jbutton.button);
            e.button = (JoystickButton)(1<<event.jbutton.button);
            e.state = joystickState;
	    e.type = JoystickButtonEventArg::PRESS;
            joystickButtonEvent.Notify(e);
            break;
        }
        case SDL_JOYBUTTONUP:{
            JoystickButtonEventArg e;
            joystickState.buttons = (JoystickButton)(joystickState.buttons & ~(1<<event.jbutton.button));
            e.button = (JoystickButton)(1<<event.jbutton.button);
            e.state = joystickState;
	    e.type = JoystickButtonEventArg::RELEASE;
            joystickButtonEvent.Notify(e);
            break;
        }
        
	} // switch on event type
    } // while sdl event
}

/**
 * Module deinitialization method.
 * Called once on engine shutdown.
 *
 * @see IModule::Deinitialize()
 */
void SDLInput::Handle(DeinitializeEventArg arg) {

}

IEvent<KeyboardEventArg>& SDLInput::KeyEvent() {
    return this->keyEvent;
}

IEvent<MouseMovedEventArg>& SDLInput::MouseMovedEvent() {
    return this->mouseMovedEvent;
}

IEvent<MouseButtonEventArg>& SDLInput::MouseButtonEvent() {
    return this->mouseButtonEvent;
}

IEvent<JoystickButtonEventArg>& SDLInput::JoystickButtonEvent() {
    return this->joystickButtonEvent;
}

IEvent<JoystickAxisEventArg>& SDLInput::JoystickAxisEvent() {
    return this->joystickAxisEvent;
}



/**
 * Hide the mouse cursor.
 *
 * @see IMouse::HideCursor()
 */
void SDLInput::HideCursor() {
    SDL_ShowCursor(SDL_DISABLE);
}

/**
 * Show the mouse cursor.
 *
 * @see IMouse::ShowCursor()
 */
void SDLInput::ShowCursor() {
    SDL_ShowCursor(SDL_ENABLE);
}

/**
 * Set cursor position.
 *
 * @param x Position on x-axis
 * @param y Position on y-axis
 *
 * @see IMouse::SetCursor()
 */
void SDLInput::SetCursor(int x, int y) {
    if (SDL_GetAppState() & SDL_APPINPUTFOCUS)
        SDL_WarpMouse(x, y);
}

/**
 * Get the current mouse state.
 *
 * @return The current mouse state
 *
 * @see IMouse::GetState()
 */
MouseState SDLInput::GetState() {
    return state;
}

} // NS Devices
} // NS OpenEngine
