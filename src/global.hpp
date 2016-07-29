#pragma once

#ifndef ARPEGGIO_GLES
#define GLEW_STATIC
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif

#include <cerrno>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

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

using namespace std;
using namespace nlohmann;
