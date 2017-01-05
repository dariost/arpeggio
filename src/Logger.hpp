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

#pragma once

#include "global.hpp"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

class Logger
{
public:
    typedef enum { DEBUG = 0, INFO, WARNING, ERROR, CRITICAL } Level;

protected:
    Level verbosity_level;
    void print(Level level, const string& message);
    template <typename T, typename... Args>
    void create_log(stringstream& buffer, const T& arg, Args... args)
    {
        buffer << arg;
        create_log(buffer, args...);
    }
    template <typename T>
    void create_log(stringstream& buffer, const T& arg)
    {
        buffer << arg;
    }
    bool is_tty;

public:
    Logger(Level min_verbosity);
    template <typename... Args>
    void log(Level level, Args... args)
    {
        if(level < verbosity_level)
            return;
        stringstream buffer;
        create_log(buffer, args...);
        print(level, buffer.str());
        if(level == CRITICAL)
            exit(EXIT_FAILURE);
    }
    template <typename T, typename U, typename... Args>
    void check(const T& arg1, const U& arg2, Level level, Args... args)
    {
        if(arg1 == arg2)
            return;
        log(level, args...);
    }
};
