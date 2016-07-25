#pragma once

#ifndef GLES
#define GLEW_STATIC
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#ifdef EXPERIMENTAL_CXX17
#include <experimental/any>
#else
#include <any>
#endif

#ifdef EXPERIMENTAL_CXX17
using namespace std::experimental;
#endif

using namespace std;
