// SDL implementation of IFrame.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _SDL_FRAME_H_
#define _SDL_FRAME_H_

#include <Display/IFrame.h>
#include <Meta/SDL.h>

namespace OpenEngine {
namespace Display {

using OpenEngine::Core::InitializeEventArg;
using OpenEngine::Core::ProcessEventArg;
using OpenEngine::Core::DeinitializeEventArg;

/**
 * SDL implementation of IFrame.
 *
 * @class SDLFrame SDLFrame.h Display/SDLFrame.h
 */
class SDLFrame : public IFrame {
private:
    // Screen settings
    int width;
    int height;
    int depth;
    FrameOption options;
    bool init;

public:
    /**
     * Default constructor.
     */
    SDLFrame(int width = 640, int height = 480, 
             int depth = 32, FrameOption options = FrameOption());
    ~SDLFrame();

    bool IsFocused() const;

    int GetWidth() const;
    int GetHeight() const;
    int GetDepth() const;
    FrameOption GetOptions() const;

    void SetWidth(const int width);
    void SetHeight(const int height);
    void SetDepth(const int depth);
    void SetOptions(const FrameOption options);

    void Handle(InitializeEventArg arg);
    void Handle(ProcessEventArg arg);
    void Handle(DeinitializeEventArg arg);

};

} // NS Display
} // NS OpenEngine

#endif
