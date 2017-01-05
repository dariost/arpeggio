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

#include "Animation.hpp"
#include "Camera.hpp"
#include "Config.hpp"
#include "Drawable.hpp"
#include "Logger.hpp"

class Actor : public Drawable
{
protected:
    shared_ptr<Logger> log;
    shared_ptr<Config> conf;
    string name;
    unordered_map<string, shared_ptr<Animation>> act;
    unordered_map<string, double> custom_height;
    double main_height;
    string current_act;
    shared_ptr<ImageManager> im;
    shared_ptr<ObjectManager> om;
    shared_ptr<Camera> camera;

public:
    Actor(shared_ptr<Logger> logger,
          const string& _name,
          shared_ptr<Config> _conf,
          shared_ptr<ImageManager> _im,
          shared_ptr<ObjectManager> _om,
          shared_ptr<Camera> _camera);
    void activateTextures(bool toggle = true);
    void exec(double pos_x, double pos_y, double horiz_perc = 1.0, double vert_perc = 1.0);
    void draw();
    void changeAct(const string& new_act);
    double getWidth();
    double getHeight();
};
