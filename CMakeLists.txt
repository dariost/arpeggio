cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

project(arpeggio)

option(DEBUG "Debug build" ON)
option(OPTIMIZE_BUILD "Use compiler optimizations" ON)

file(GLOB SOURCES src/*.cpp)

if(DEBUG AND (NOT MSVC))
    set(LIBS ${LIBS} -g)
    set(FLAGS ${FLAGS} -g)
endif()

if(NOT WIN32)
    find_package(GLES REQUIRED)
    set(LIBS ${LIBS} ${GLES_LIBRARIES})
endif()

add_subdirectory(3rd)

if(WIN32)
    set(LIBS ${LIBS} glew)
endif()
set(LIBS ${LIBS} SDL2-static SDL2main)
set(LIBS ${LIBS} SDL2_image)
set(LIBS ${LIBS} SDL2_mixer)
set(LIBS ${LIBS} SDL2_net)
set(LIBS ${LIBS} SDL2_ttf)
set(LIBS ${LIBS} freetype)
set(LIBS ${LIBS} bz2)
if(WIN32)
	set(LIBS ${LIBS} ws2_32 iphlpapi glu32 opengl32 gdi32 user32 kernel32)
endif()

if(WIN32)
    set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${glew_INCLUDES})
endif()
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${JSON_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_image_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_mixer_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_net_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_ttf_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${bz2_INCLUDES})

if(MINGW)
    if(DEBUG)
    set(LIBS ${LIBS} -mconsole)
    else()
    set(LIBS ${LIBS} -mwindows)
    endif()
endif()

if(UNIX)
    set(LIBS ${LIBS} -Wl,-O1,--sort-common,--as-needed,-z,relro -flto)
    set(FLAGS ${FLAGS} -flto)
endif()

if(NOT MSVC)
set(FLAGS ${FLAGS} -Wall -Wextra -Werror -std=gnu++14)

if(OPTIMIZE_BUILD)
    set(FLAGS ${FLAGS} -O3)
else()
    set(FLAGS ${FLAGS} -O0)
endif()
endif()

add_executable(arpeggio ${SOURCES})

target_include_directories(arpeggio PRIVATE ${GLOBAL_INCLUDES})

target_link_libraries(arpeggio PRIVATE ${LIBS})

target_compile_options(arpeggio PRIVATE ${FLAGS})

if(DEBUG)
    set(DEFS ${DEFS} ARPEGGIO_DEBUG)
endif()

if(NOT WIN32)
    set(DEFS ${DEFS} ARPEGGIO_GLES)
endif()

if(MINGW)
    set(DEFS ${DEFS} SDL_MAIN_HANDLED)
endif()

target_compile_definitions(arpeggio PRIVATE ${DEFS})
