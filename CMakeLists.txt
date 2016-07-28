cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

project(arpeggio)

option(DEBUG "Debug build" ON)
option(EXPERIMENTAL_CXX17 "Use experimental C++17" ON)
option(OPTIMIZE_BUILD "Use compiler optimizations" ON)

file(GLOB SOURCES src/*.cpp)

if(DEBUG)
    set(LIBS ${LIBS} -g)
    set(FLAGS ${FLAGS} -g)
endif()

if(NOT WIN32)
    find_package(GLES REQUIRED)
    set(LIBS ${LIBS} ${GLES_LIBRARIES})
endif()

add_subdirectory(3rd)

if(WIN32)
    set(LIBS ${LIBS} glew -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32)
endif()
set(LIBS ${LIBS} SDL2-static SDL2main)
set(LIBS ${LIBS} SDL2_image)
set(LIBS ${LIBS} SDL2_mixer)
set(LIBS ${LIBS} SDL2_net)
set(LIBS ${LIBS} SDL2_ttf)
set(LIBS ${LIBS} freetype)
set(LIBS ${LIBS} bz2)
if(WIN32)
	set(LIBS ${LIBS} -lws2_32 -liphlpapi)
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

set(FLAGS ${FLAGS} -Wall -Wextra -Werror)

if(OPTIMIZE_BUILD)
    set(FLAGS ${FLAGS} -O3)
else()
    set(FLAGS ${FLAGS} -O0)
endif()

add_executable(arpeggio ${SOURCES})

target_include_directories(arpeggio PRIVATE ${GLOBAL_INCLUDES})

target_link_libraries(arpeggio PRIVATE ${LIBS})

if(EXPERIMENTAL_CXX17)
    set(FLAGS ${FLAGS} -std=gnu++1z)
    set(DEFS ${DEFS} ARPEGGIO_EXPERIMENTAL_CXX17)
else()
    set(FLAGS ${FLAGS} -std=gnu++17)
endif()

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
