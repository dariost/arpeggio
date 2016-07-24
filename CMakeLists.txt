cmake_minimum_required(VERSION 3.0.2)

project(arpeggio)

option(DEBUG "Debug build" ON)
option(GLES "Use OpenGL ES" OFF)

file(GLOB SOURCES src/*.cpp)

if(MINGW)
    set(LIBS ${LIBS} -mwindows)
endif()

if(UNIX)
    set(LIBS ${LIBS} -Wl,-O1,--sort-common,--as-needed,-z,relro -flto)
    set(FLAGS ${FLAGS} -flto)
endif()

set(FLAGS ${FLAGS} -std=gnu++1z -O3 -Wall -Wextra -Werror)

add_executable(arpeggio ${SOURCES})

#target_include_directories(arpeggio PRIVATE ${YAML_INCLUDES} ${SDL2_INCLUDES} ${SDL2_image_INCLUDES} ${SDL2_mixer_INCLUDES} ${SDL2_ttf_INCLUDES} ${SDL2_net_INCLUDES} ${ZLIB_INCLUDES} ${DUKTAPE_INCLUDES})

target_link_libraries(arpeggio PRIVATE ${LIBS})

target_compile_options(arpeggio PRIVATE ${FLAGS})

if(GLES)
    set(DEFS ${DEFS} GLES)
endif()

if(DEBUG)
    set(DEFS ${DEFS} DEBUG)
endif()

target_compile_definitions(arpeggio PRIVATE ${DEFS})

