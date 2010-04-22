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

/**
 * SDL implementation of IFrame.
 *
 * @class SDLFrame SDLFrame.h Display/SDLFrame.h
 */
class SDLFrame : public IFrame {
private:
    // Screen settings
    unsigned int width, height, depth;
    FrameOption options;
    bool init;
    IViewingVolume* dummycam;
    StereoCamera* stereo;
    
    void CreateSurface();

public:
    /**
     * Default constructor.
     */
    SDLFrame(int width = 640, int height = 480, 
             int depth = 32, FrameOption options = FrameOption());
    ~SDLFrame();

    bool IsFocused() const;

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;
    unsigned int GetDepth() const;
    FrameOption GetOptions() const;
    bool GetOption(const FrameOption option) const;

    void SetWidth(const unsigned int width);
    void SetHeight(const unsigned int height);
    void SetDepth(const unsigned int depth);
    void SetOptions(const FrameOption options);
    void ToggleOption(const FrameOption option);

    void Handle(Core::InitializeEventArg arg);
    void Handle(Core::ProcessEventArg arg);
    void Handle(Core::DeinitializeEventArg arg);

    void SetViewingVolume(IViewingVolume* vv);
    StereoCamera& GetStereoCamera() const;
};

} // NS Display
} // NS OpenEngine

#endif
