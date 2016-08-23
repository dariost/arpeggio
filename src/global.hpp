#pragma once

#ifndef ARPEGGIO_GLES
#define GLEW_STATIC
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif

#include <array>
#include <cerrno>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <future>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

#ifdef _WIN32
#include <io.h>
#include <windows.h>
#undef ERROR
#else
#include <unistd.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <duktape.h>
#include <json.hpp>

using namespace std;
using namespace nlohmann;

#define ARPEGGIO_MAX_TEXTURE_SIZE 4096

#ifdef ARPEGGIO_DEBUG
#ifndef UWP
#define USE_GLDEBUG
#endif
#endif
