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

#include "Config.hpp"
#include "ImageManager.hpp"
#include "Logger.hpp"
#include "ObjectManager.hpp"
#include "Scenario.hpp"
#include "Timer.hpp"

class Application
{
protected:
    shared_ptr<Logger> log;
    shared_ptr<Config> global_config;
    shared_ptr<Config> app_config;
    shared_ptr<ObjectManager> object_manager;
    shared_ptr<ImageManager> image_manager;
    shared_ptr<Scenario> scenario;
    SDL_Window* window;
    SDL_GLContext glcon;
    bool should_quit;
    int real_width;
    int real_height;

public:
    Application(int argc, char** argv);
    ~Application();
    int run();
    friend void internal_run(void* _app);
};
