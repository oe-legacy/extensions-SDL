SET( EXTENSION_NAME "Extensions_SDL")

ADD_LIBRARY( ${EXTENSION_NAME}
  Display/SDLEnvironment.h
  Devices/SDLInput.h
  Devices/SDLInput.cpp
  Display/SDLFrame.h
  Display/SDLFrame.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
   ${SDL_LIBRARY}
)
