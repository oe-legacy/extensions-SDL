// SDL implementation of IFrame
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Core/Exceptions.h>
#include <Display/SDLFrame.h>
#include <Meta/OpenGL.h>
#include <string>

namespace OpenEngine {
namespace Display {

using OpenEngine::Core::Exception;
using std::string;
    
SDLFrame::SDLFrame(int width, int height, int depth, FrameOption options)
    : IFrame(width, height, depth, options),
      width(width),
      height(height),
      depth(depth),
      options(FrameOption(options|FRAME_OPENGL)),
      init(false) {}

SDLFrame::~SDLFrame() {

}

bool SDLFrame::IsFocused() const {
    return ((SDL_GetAppState() & SDL_APPINPUTFOCUS) != 0);
}

int SDLFrame::GetWidth() const {
    return width;
}

int SDLFrame::GetHeight() const {
    return height;
}

int SDLFrame::GetDepth() const {
    return depth;
}

FrameOption SDLFrame::GetOptions() const {
    return options;
}

void SDLFrame::SetWidth(const int width) {
    if (!init) this->width = width;
}

void SDLFrame::SetHeight(const int height) {
    if (!init) this->height = height;
}

void SDLFrame::SetDepth(const int depth) {
    if (!init) this->depth = depth;
}

void SDLFrame::SetOptions(const FrameOption options) {
    if (!init) this->options = options;
}

void SDLFrame::Handle(InitializeEventArg arg) {
    // Initialize the video frame
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 )
        throw Exception("SDL_Init: " + string(SDL_GetError()));

    // Set SDL flags
    Uint32 flags = options;

    // Use hardware rendered surface as default
    flags |= SDL_HWSURFACE;

    // Create window
    if (SDL_SetVideoMode(width, height, depth, flags) == NULL)
        throw Exception("SDL_SetVideoMode: " + string(SDL_GetError()));

    // Set the private initialization flag
    init = true;
}

void SDLFrame::Handle(ProcessEventArg arg) {
    // Start by flipping the screen which is the
    // result from last engine loop.
    if (IsOptionSet(FRAME_OPENGL))
        SDL_GL_SwapBuffers();
    // Clear the screen and the depth buffer.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void SDLFrame::Handle(DeinitializeEventArg arg) {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

} // NS Display
} // NS OpenGL
