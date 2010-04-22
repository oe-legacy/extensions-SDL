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
#include <Display/StereoCamera.h>
#include <Display/ViewingVolume.h>

#include <string>

namespace OpenEngine {
namespace Display {

using OpenEngine::Core::Exception;
using std::string;
    
SDLFrame::SDLFrame(int width, int height, int depth, FrameOption options)
    : width(width)
    , height(height)
    , depth(depth)
    , options(FrameOption(options|FRAME_OPENGL)) 
    , init(false) 
    , dummycam(new ViewingVolume())
    , stereo(new StereoCamera(*dummycam))
{

}

SDLFrame::~SDLFrame() {

}

bool SDLFrame::IsFocused() const {
    return ((SDL_GetAppState() & SDL_APPINPUTFOCUS) != 0);
}

unsigned int SDLFrame::GetWidth() const {
    return width;
}

unsigned int SDLFrame::GetHeight() const {
    return height;
}

unsigned int SDLFrame::GetDepth() const {
    return depth;
}

FrameOption SDLFrame::GetOptions() const {
    return options;
}

bool SDLFrame::GetOption(const FrameOption option) const {
    return (option & GetOptions()) == option;
}

void SDLFrame::SetWidth(const unsigned int width) {
    if (!init) this->width = width;
}

void SDLFrame::SetHeight(const unsigned int height) {
    if (!init) this->height = height;
}

void SDLFrame::SetDepth(const unsigned int depth) {
    if (!init) this->depth = depth;
}

void SDLFrame::SetOptions(const FrameOption options) {
    bool reload = false;
    if (options != this->options) reload = true;
    this->options = options;
    if (init && reload) {
        CreateSurface();
    }
}

void SDLFrame::ToggleOption(const FrameOption option) {
    FrameOption opt = FrameOption(options ^ option);
    SetOptions(opt);
}

void SDLFrame::CreateSurface() {
    // Set SDL flags
    Uint32 flags = options;

    // Use hardware rendered surface as default
    flags |= SDL_HWSURFACE;

    // Create window
    if (SDL_SetVideoMode(width, height, depth, flags) == NULL)
        throw Exception("SDL_SetVideoMode: " + string(SDL_GetError()));

    /* @todo
      use signaling to reload gl context objects
      
      see, user comment 2 on:
      http://www.libsdl.org/cgi/docwiki.cgi/SDL_SetVideoMode
      causes gl context to unload: textures and vertex arrays
    */
}

void SDLFrame::Handle(Core::InitializeEventArg arg) {
    // Initialize the video frame
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
        throw Exception("SDL_Init: " + string(SDL_GetError()));

    CreateSurface();

    // Set the private initialization flag
    init = true;
    initEvent.Notify(InitializeEventArg(*this));
}

void SDLFrame::Handle(Core::ProcessEventArg arg) {
    // Start by flipping the screen which is the
    // result from last engine loop.
    redrawEvent.Notify(RedrawEventArg(*this, arg.start, arg.approx));
    if (IsOptionSet(FRAME_OPENGL))
        SDL_GL_SwapBuffers();
}

void SDLFrame::Handle(Core::DeinitializeEventArg arg) {
    deinitEvent.Notify(DeinitializeEventArg(*this));
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

StereoCamera& SDLFrame::GetStereoCamera() const {
    return *stereo;
}

void SDLFrame::SetViewingVolume(IViewingVolume* vv) {
    this->vv = vv;
    stereo->SetViewingVolume(*vv);
}

} // NS Display
} // NS OpenGL
