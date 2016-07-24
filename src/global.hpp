#pragma once

#ifdef _WIN32
#define GLEW_STATIC
#include <GL/glew.h>
#else
#include <GLES3/gl3.h>
#endif
