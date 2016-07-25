cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake-modules/")

project(arpeggio)

option(DEBUG "Debug build" ON)
option(EXPERIMENTAL_CXX17 "Use experimental C++17" ON)

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
set(LIBS ${LIBS} jsoncpp_lib_static)
set(LIBS ${LIBS} SDL2_image)

if(WIN32)
    set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${glew_INCLUDES})
endif()
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${jsoncpp_INCLUDES})
set(GLOBAL_INCLUDES ${GLOBAL_INCLUDES} ${SDL2_image_INCLUDES})

if(MINGW)
    set(LIBS ${LIBS} -mwindows)
endif()

if(UNIX)
    set(LIBS ${LIBS} -Wl,-O1,--sort-common,--as-needed,-z,relro -flto)
    set(FLAGS ${FLAGS} -flto)
endif()

set(FLAGS ${FLAGS} -O3 -Wall -Wextra -Werror)

add_executable(arpeggio ${SOURCES})

target_include_directories(arpeggio PRIVATE ${GLOBAL_INCLUDES})

target_link_libraries(arpeggio PRIVATE ${LIBS})

if(EXPERIMENTAL_CXX17)
    set(FLAGS ${FLAGS} -std=gnu++1z)
    set(DEFS ${DEFS} EXPERIMENTAL_CXX17)
else()
    set(FLAGS ${FLAGS} -std=gnu++17)
endif()

target_compile_options(arpeggio PRIVATE ${FLAGS})

if(DEBUG)
    set(DEFS ${DEFS} DEBUG)
endif()

if(NOT WIN32)
    set(DEFS ${DEFS} GLES)
endif()

target_compile_definitions(arpeggio PRIVATE ${DEFS})
