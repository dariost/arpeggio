/*
 * Copyright © [2016; 2017] | Dario Ostuni <dario.ostuni@gmail.com>
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/

#include "GLDebug.hpp"

PFNGLDEBUGMESSAGECALLBACKPROC fpDebugMessageCallback;
PFNGLDEBUGMESSAGECONTROLPROC fpDebugMessageControl;
PFNGLDEBUGMESSAGEINSERTPROC fpDebugMessageInsert;
PFNGLGETDEBUGMESSAGELOGPROC fpGetDebugMessageLog;
PFNGLGETOBJECTLABELPROC fpGetObjectLabel;
PFNGLGETOBJECTPTRLABELPROC fpGetObjectPtrLabel;
PFNGLOBJECTLABELPROC fpObjectLabel;
PFNGLOBJECTPTRLABELPROC fpObjectPtrLabel;
PFNGLPOPDEBUGGROUPPROC fpPopDebugGroup;
PFNGLPUSHDEBUGGROUPPROC fpPushDebugGroup;

void GLAPIENTRY gl_callback(GLenum source,
                            GLenum type,
                            GLuint id,
                            GLenum severity,
                            GLsizei length,
                            const GLchar* message,
                            const void* user_param)
{
    (void)length;
    Logger* log = (Logger*)user_param;
#ifdef ARPEGGIO_GLES
    string ogls = "OpenGL ES";
#else
    string ogls = "OpenGL";
#endif
    stringstream ss;
    ss << ogls << " message #" << id << " (From: ";
    if(source == GL_DEBUG_SOURCE_API)
        ss << ogls << " API";
    else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM)
        ss << "Window System";
    else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER)
        ss << "Shader Compiler";
    else if(source == GL_DEBUG_SOURCE_THIRD_PARTY)
        ss << "Third Party Application";
    else if(source == GL_DEBUG_SOURCE_APPLICATION)
        ss << "Application";
    else if(source == GL_DEBUG_SOURCE_OTHER)
        ss << "Unknown";
    else
        ss << "NULL";
    ss << " - Type: ";
    if(type == GL_DEBUG_TYPE_ERROR)
        ss << "Error";
    else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
        ss << "Deprecated Behavior";
    else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
        ss << "Undefined Behavior";
    else if(type == GL_DEBUG_TYPE_PORTABILITY)
        ss << "Portability";
    else if(type == GL_DEBUG_TYPE_PERFORMANCE)
        ss << "Performance";
    else if(type == GL_DEBUG_TYPE_MARKER)
        ss << "Marker";
    else if(type == GL_DEBUG_TYPE_PUSH_GROUP)
        ss << "Push Group";
    else if(type == GL_DEBUG_TYPE_POP_GROUP)
        ss << "Pop Group";
    else if(type == GL_DEBUG_TYPE_OTHER)
        ss << "Unknown";
    else
        ss << "NULL";
    ss << "): " << message;
    Logger::Level verbosity = Logger::Level::CRITICAL;
    if(severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        verbosity = Logger::Level::DEBUG;
    else if(severity == GL_DEBUG_SEVERITY_LOW)
        verbosity = Logger::Level::WARNING;
    else if(severity == GL_DEBUG_SEVERITY_MEDIUM)
        verbosity = Logger::Level::ERROR;
    else if(severity == GL_DEBUG_SEVERITY_HIGH)
        verbosity = Logger::Level::CRITICAL;
    log->log(verbosity, ss.str());
}

#define get_gl_proc(ptr_t, gl_fun)                           \
    fp##gl_fun = (ptr_t)SDL_GL_GetProcAddress("gl" #gl_fun); \
    log->check(!fp##gl_fun, false, Logger::Level::CRITICAL, "Cannot get function \"", "gl" #gl_fun, "\"");

void gldebug_init_functions(shared_ptr<Logger> log)
{
    get_gl_proc(PFNGLDEBUGMESSAGECALLBACKPROC, DebugMessageCallback);
    get_gl_proc(PFNGLDEBUGMESSAGECONTROLPROC, DebugMessageControl);
    get_gl_proc(PFNGLDEBUGMESSAGEINSERTPROC, DebugMessageInsert);
    get_gl_proc(PFNGLGETDEBUGMESSAGELOGPROC, GetDebugMessageLog);
    get_gl_proc(PFNGLGETOBJECTLABELPROC, GetObjectLabel);
    get_gl_proc(PFNGLGETOBJECTPTRLABELPROC, GetObjectPtrLabel);
    get_gl_proc(PFNGLOBJECTLABELPROC, ObjectLabel);
    get_gl_proc(PFNGLOBJECTPTRLABELPROC, ObjectPtrLabel);
    get_gl_proc(PFNGLPOPDEBUGGROUPPROC, PopDebugGroup);
    get_gl_proc(PFNGLPUSHDEBUGGROUPPROC, PushDebugGroup);
    fpDebugMessageCallback(gl_callback, log.get());
}
