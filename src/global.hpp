#pragma once

#ifndef ARPEGGIO_GLES
#define GLEW_STATIC
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif

#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#ifdef ARPEGGIO_EXPERIMENTAL_CXX17
#include <experimental/any>
#else
#include <any>
#endif

#ifdef _WIN32
#include <winsock2.h>

#include <io.h>
#include <windows.h>
#undef ERROR
#else
#include <unistd.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#include <SDL_ttf.h>
#include <json.hpp>

#ifdef ARPEGGIO_EXPERIMENTAL_CXX17
using namespace std::experimental;
#endif

using namespace std;
using namespace nlohmann;
