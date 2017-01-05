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

#include "Actor.hpp"

Actor::Actor(shared_ptr<Logger> logger,
             const string& _name,
             shared_ptr<Config> _conf,
             shared_ptr<ImageManager> _im,
             shared_ptr<ObjectManager> _om,
             shared_ptr<Camera> _camera)
{
    log = logger;
    name = _name;
    conf = _conf;
    im = _im;
    om = _om;
    camera = _camera;
    main_height = conf->get("height", 1.0);
    auto animation_json = conf->get_json("acts");
    unordered_map<string, string> animation;
    bool at_least_one = false;
    for(auto it = animation_json.begin(); it != animation_json.end(); ++it)
    {
        animation[it.key()] = it.value();
        at_least_one = true;
    }
    log->check(at_least_one, true, Logger::Level::WARNING, "Actor \"", name, "\" has no acts");
    custom_height = conf->get<unordered_map<string, double>>("acts_height");
    current_act = conf->get<string>("main_act");
    for(auto& i : animation)
    {
        auto tmp_conf = make_shared<Config>(log);
        tmp_conf->parseConfig(om->getObject(string("animations/") + i.second + "/animation.json"));
        act[i.first] = make_shared<Animation>(log, tmp_conf, im, i.second);
    }
    log->check(
        act.count(current_act), 1UL, Logger::Level::CRITICAL, "Actor \"", name, "\" doesn't know how to \"", current_act, "\"");
}

void Actor::changeAct(const string& new_act)
{
    current_act = new_act;
    log->check(
        act.count(current_act), 1UL, Logger::Level::CRITICAL, "Actor \"", name, "\" doesn't know how to \"", current_act, "\"");
}

double Actor::getWidth()
{
    log->check(
        act.count(current_act), 1UL, Logger::Level::CRITICAL, "Actor \"", name, "\" doesn't know how to \"", current_act, "\"");
    double height = main_height;
    if(custom_height.count(current_act))
        height = custom_height[current_act];
    return height * act[current_act]->getAspectRatio();
}

double Actor::getHeight()
{
    log->check(
        act.count(current_act), 1UL, Logger::Level::CRITICAL, "Actor \"", name, "\" doesn't know how to \"", current_act, "\"");
    double height = main_height;
    if(custom_height.count(current_act))
        height = custom_height[current_act];
    return height;
}

void Actor::exec(double pos_x, double pos_y, double horiz_perc, double vert_perc)
{
    log->check(
        act.count(current_act), 1UL, Logger::Level::CRITICAL, "Actor \"", name, "\" doesn't know how to \"", current_act, "\"");
    log->check(
        horiz_perc >= 0.0 && horiz_perc <= 1.0, true, Logger::Level::CRITICAL, "Invalid texture crop in actor \"", name, "\"");
    log->check(vert_perc >= 0.0 && vert_perc <= 1.0, true, Logger::Level::CRITICAL, "Invalid texture crop in actor \"", name, "\"");
    double height = main_height;
    if(custom_height.count(current_act))
        height = custom_height[current_act];
    double aspect_ratio = act[current_act]->getAspectRatio();
    double width = height * aspect_ratio;
    array<GLfloat, 16> data;
    pair<double, double> tmp;
    // Lower-left corner
    tmp = camera->getPoint(pos_x, pos_y);
    data[0] = tmp.first;
    data[1] = tmp.second;
    data[2] = 0.0;
    data[3] = 1.0;
    // Lower-right corner
    tmp = camera->getPoint(pos_x + width, pos_y);
    data[4] = tmp.first;
    data[5] = tmp.second;
    data[6] = horiz_perc;
    data[7] = 1.0;
    // Upper-left corner
    tmp = camera->getPoint(pos_x, pos_y + height);
    data[8] = tmp.first;
    data[9] = tmp.second;
    data[10] = 0.0;
    data[11] = 1.0 - vert_perc;
    // Upper-right corner
    tmp = camera->getPoint(pos_x + width, pos_y + height);
    data[12] = tmp.first;
    data[13] = tmp.second;
    data[14] = horiz_perc;
    data[15] = 1.0 - vert_perc;
    if(data != act[current_act]->getData())
        act[current_act]->updateData(data);
}

void Actor::draw()
{
    log->check(
        act.count(current_act), 1UL, Logger::Level::CRITICAL, "Actor \"", name, "\" doesn't know how to \"", current_act, "\"");
    auto data = act[current_act]->getData();
    float w = min(1.0f, data[4]) - max(-1.0f, data[0]);
    float h = min(1.0f, data[9]) - max(-1.0f, data[1]);
    if(h > 0.0f && w > 0.0f)
        act[current_act]->draw();
}

void Actor::activateTextures(bool toggle)
{
    for(auto& i : act)
    {
        i.second->activateTextures(toggle);
    }
}
