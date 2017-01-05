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
#include "Image.hpp"
#include "ImageManager.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

class Animation
{
protected:
    shared_ptr<Logger> log;
    string name;
    array<GLfloat, 16> data;
    Timer timer;
    vector<shared_ptr<Image>> frame;
    double fps;
    size_t getActualFrameNumber();
    GLuint vao;
    GLuint vbo;
    double aspect_ratio;

public:
    Animation(shared_ptr<Logger> logger, shared_ptr<Config> desc, shared_ptr<ImageManager> image_manager, const string& _name);
    ~Animation();
    void setFrames(const vector<shared_ptr<Image>>& v);
    void setFPS(double f);
    void updateData(const array<GLfloat, 16>& d);
    array<GLfloat, 16> getData();
    void draw();
    void activateTextures(bool toggle = true);
    double getAspectRatio();
};
