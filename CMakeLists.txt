
ADD_LIBRARY(Extensions_SDL
  Devices/SDLInput.cpp
  Display/SDLFrame.cpp
)

TARGET_LINK_LIBRARIES(Extensions_SDL
   Extensions_OpenGLRenderer
   ${SDL_LIBRARY}
)
