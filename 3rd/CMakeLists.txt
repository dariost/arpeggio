cmake_minimum_required(VERSION 3.0.2)

set(SDL_SHARED_ENABLED_BY_DEFAULT OFF CACHE BOOL "Build static SDL2")
option(DIRECTX "Disable DirectX" OFF)
option(RENDER_D3D "Disable Direct3D" OFF)
if(WIN32)
    option(VIDEO_OPENGLES "Disable OpenGL ES on Windows" OFF)
endif()

add_subdirectory(SDL2-2.0.4)

set(SDL2_INCLUDES ${SDL2_SOURCE_DIR}/include PARENT_SCOPE)
