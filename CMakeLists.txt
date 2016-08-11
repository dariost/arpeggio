cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

include(CheckCXXCompilerFlag)

project(arpeggio)

option(DEBUG "Debug build" ON)

message(STATUS "Building on: ${CMAKE_SYSTEM_NAME}")

if(WIN32 OR (CMAKE_SYSTEM_NAME STREQUAL "FreeBSD") OR (CMAKE_SYSTEM_NAME STREQUAL "Haiku"))
    set(USE_GLEW ON)
else()
    set(USE_GLEW OFF)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
  set(CMAKE_REQUIRED_INCLUDES "/usr/local/include" "/usr/include")
endif()

file(GLOB SOURCES src/*.cpp)

if(DEBUG AND (NOT MSVC))
    set(LIBS ${LIBS} -g)
    set(FLAGS ${FLAGS} -g)
endif()

if(NOT (USE_GLEW OR EMSCRIPTEN))
    find_package(GLES REQUIRED)
    set(LIBS ${LIBS} ${GLES_LIBRARIES})
endif()

add_subdirectory(3rd)

if(USE_GLEW)
    set(LIBS ${LIBS} glew)
endif()
set(LIBS ${LIBS} SDL2-static SDL2main)
set(LIBS ${LIBS} SDL2_image)
set(LIBS ${LIBS} SDL2_mixer)
set(LIBS ${LIBS} SDL2_net)
set(LIBS ${LIBS} SDL2_ttf)
set(LIBS ${LIBS} freetype)
set(LIBS ${LIBS} lib_bz2)
set(LIBS ${LIBS} hashlib2plus)
if(USE_GLEW)
    if(WIN32)
    	set(LIBS ${LIBS} ws2_32 iphlpapi glu32 opengl32 gdi32 user32 kernel32)
    else()
        set(LIBS ${LIBS} -L/usr/local/lib GL GLU)
    endif()
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Haiku")
    set(LIBS ${LIBS} network be game)
endif()

if(USE_GLEW)
    set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${glew_INCLUDES})
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
    set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} "/usr/local/include")
endif()
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${JSON_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_image_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_mixer_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_net_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_ttf_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${lib_bz2_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${hashlib2plus_INCLUDES})

if(MINGW)
    if(DEBUG)
    set(LIBS ${LIBS} -mconsole)
    else()
    set(LIBS ${LIBS} -mwindows)
    endif()
endif()

if(UNIX)
    set(LIBS ${LIBS} -Wl,-O1,--sort-common,--as-needed,-z,relro)
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(FLAGS ${FLAGS} -flto)
        set(LIBS ${LIBS} -flto)
    endif()
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
    set(LIBS ${LIBS} -static-libgcc -static-libstdc++)
endif()

if(NOT MSVC)
    CHECK_CXX_COMPILER_FLAG("-std=gnu++14" COMPILER_SUPPORTS_GNUXX14)

    if(COMPILER_SUPPORTS_GNUXX14)
        set(FLAGS ${FLAGS} -std=gnu++14)
    else()
        set(FLAGS ${FLAGS} -std=gnu++1y)
    endif()

    set(FLAGS ${FLAGS} -Wall -Wextra -Werror -O3)
endif()

add_executable(arpeggio ${SOURCES})

target_include_directories(arpeggio PRIVATE ${GLOBAL_INCLUDES})

target_link_libraries(arpeggio PRIVATE ${LIBS})

target_compile_options(arpeggio PRIVATE ${FLAGS})

if(DEBUG)
    set(DEFS ${DEFS} ARPEGGIO_DEBUG)
endif()

if((NOT USE_GLEW) OR EMSCRIPTEN)
    set(DEFS ${DEFS} ARPEGGIO_GLES)
endif()

if(MINGW)
    set(DEFS ${DEFS} SDL_MAIN_HANDLED)
endif()

target_compile_definitions(arpeggio PRIVATE ${DEFS})
