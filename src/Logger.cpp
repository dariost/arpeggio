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

#include "Logger.hpp"

void Logger::print(Level level, const string& message)
{
    string msg;
    if(level == DEBUG)
        msg = "[DEBUG] " + message;
    else if(level == INFO)
        msg = "[INFO] " + message;
    else if(level == WARNING)
        msg = "[WARNING] " + message;
    else if(level == ERROR)
        msg = "[ERROR] " + message;
    else if(level == CRITICAL)
        msg = "[CRITICAL] " + message;

    if(is_tty)
    {
        if(level == DEBUG)
            msg = ANSI_COLOR_CYAN + msg;
        else if(level == INFO)
            msg = ANSI_COLOR_GREEN + msg;
        else if(level == WARNING)
            msg = ANSI_COLOR_YELLOW + msg;
        else if(level == ERROR)
            msg = ANSI_COLOR_RED + msg;
        else if(level == CRITICAL)
            msg = ANSI_COLOR_MAGENTA + msg;
        msg = msg + ANSI_COLOR_RESET;
    }

    cout << msg << endl;
}

Logger::Logger(Level min_verbosity)
{
    verbosity_level = min_verbosity;
#ifdef UWP
    is_tty = false;
#elif defined(_WIN32)
    is_tty = _isatty(_fileno(stdout));
#else
    is_tty = isatty(fileno(stdout));
#endif
}
