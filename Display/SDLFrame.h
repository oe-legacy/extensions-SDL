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
#include <Display/ICanvas.h>
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
    class FrameCanvas: public ICanvas {
    private:
        IFrame& frame;
    public:
        FrameCanvas(IFrame& frame): frame(frame) {}
        virtual ~FrameCanvas() {}
        unsigned int GetWidth() const { return frame.GetWidth(); }
        unsigned int GetHeight() const { return frame.GetHeight(); }
        unsigned int GetDepth() const { return frame.GetDepth(); }
        void SetWidth(const unsigned int width) { frame.SetWidth(width); }
        void SetHeight(const unsigned int height) { frame.SetHeight(height); }
        void SetDepth(const unsigned int depth) { frame.SetDepth(depth); }

        void Handle(Display::InitializeEventArg arg) {}
        void Handle(Display::DeinitializeEventArg arg) {}
        void Handle(Display::ProcessEventArg arg) {}
        void Handle(Display::ResizeEventArg arg) {}

        ITexture2DPtr GetTexture() { return ITexture2DPtr(); }
    };

    // Screen settings
    unsigned int width, height, depth;
    FrameOption options;
    bool init;
    
    ICanvas* canvas;
    FrameCanvas fc;
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

    void SetCanvas(ICanvas* canvas) { this->canvas = canvas; }
    ICanvas* GetCanvas() { return canvas; }
};

} // NS Display
} // NS OpenEngine

#endif
