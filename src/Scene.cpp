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

#include "Scene.hpp"

Scene::Scene(shared_ptr<Logger> logger,
             string _name,
             shared_ptr<Config> _conf,
             double _real_width,
             double _real_height,
             shared_ptr<ImageManager> _im,
             shared_ptr<ObjectManager> _om)
{
    log = logger;
    name = _name;
    conf = _conf;
    real_width = _real_width;
    real_height = _real_height;
    im = _im;
    om = _om;
    js_ctx = duk_create_heap_default();
    log->check(!js_ctx, false, Logger::Level::CRITICAL, "Cannot start JavaScript VM in scene \"", name, "\"");
    render_priority = conf->get("render_priority", 0.0);
    double camera_height = conf->get("camera_height", 2.0);
    double camera_pos_x = conf->get("camera_pos_x", 0.0);
    double camera_pos_y = conf->get("camera_pos_y", 0.0);
    camera = make_shared<Camera>(log, real_width, real_height, camera_height, camera_pos_x, camera_pos_y);
    string initial_eval;
    initial_eval += "var camera_width = ";
    initial_eval += to_string(camera->getWidth());
    initial_eval += "; var camera_height = ";
    initial_eval += to_string(camera->getHeight());
    initial_eval += "; var actor_width = -1.0; var actor_height = -1.0;";
    duk_eval_string_noresult(js_ctx, initial_eval.data());
    auto tmp_v = conf->getv("actors");
    log->check(tmp_v.size() != 0, true, Logger::Level::WARNING, "Scene \"", name, "\" has no actors");
    for(auto& i : tmp_v)
    {
        auto js_check = [&](duk_int_t ret) -> void {
            log->check(ret, 0, Logger::Level::CRITICAL, "Error while evaluating JavaScript: ", duk_safe_to_string(js_ctx, -1));
        };
        auto c = make_shared<Config>(log, conf->getName(), conf->getRelativeName());
        c->parseConfig(i.dump());
        string actor_pos_x = c->get<string>("pos_x", "0.0");
        string actor_pos_y = c->get<string>("pos_y", "0.0");
        string actor_class = c->get<string>("class");
        string actor_name = c->get<string>("name");
        double absolute_priority = c->get("absolute_priority", 0.0);
        auto actor_class_conf = make_shared<Config>(log);
        actor_class_conf->parseConfig(om->getObject(string("actors/") + actor_class + "/actor.json"));
        auto tmp_actor = make_shared<Actor>(log, actor_name, actor_class_conf, im, om, camera);
        double actor_actual_pos_x, actor_actual_pos_y;
        string tmp_js_eval;
        tmp_js_eval = string("actor_width = ") + to_string(tmp_actor->getWidth());
        js_check(duk_peval_string(js_ctx, tmp_js_eval.c_str()));
        duk_pop(js_ctx);
        tmp_js_eval = string("actor_height = ") + to_string(tmp_actor->getHeight());
        js_check(duk_peval_string(js_ctx, tmp_js_eval.c_str()));
        duk_pop(js_ctx);
        js_check(duk_peval_string(js_ctx, actor_pos_x.c_str()));
        actor_actual_pos_x = duk_to_number(js_ctx, -1);
        log->check(isfinite(actor_actual_pos_x),
                   true,
                   Logger::Level::CRITICAL,
                   "Failed to evaluate JavaScript: actor \"",
                   actor_name,
                   "\" returned a non finite pos_x");
        duk_pop(js_ctx);
        js_check(duk_peval_string(js_ctx, actor_pos_y.c_str()));
        actor_actual_pos_y = duk_to_number(js_ctx, -1);
        log->check(isfinite(actor_actual_pos_y),
                   true,
                   Logger::Level::CRITICAL,
                   "Failed to evaluate JavaScript: actor \"",
                   actor_name,
                   "\" returned a non finite pos_y");
        duk_pop(js_ctx);
        log->check(actors.count(actor_name),
                   0UL,
                   Logger::Level::ERROR,
                   "In scene \"",
                   name,
                   "\" an actor with name \"",
                   actor_name,
                   "\" already exists: all subsequent actors will be shadowed");
        actors[actor_name] = actor_data(tmp_actor, actor_actual_pos_x, actor_actual_pos_y, absolute_priority);
    }
}

Scene::~Scene()
{
    duk_destroy_heap(js_ctx);
}

void Scene::activateTextures(bool toggle)
{
    for(auto& i : actors)
        i.second.actor->activateTextures(toggle);
}

void Scene::draw()
{
    priority_queue<actor_data> pq;
    for(auto& i : actors)
        pq.push(i.second);
    while(!pq.empty())
    {
        auto tmp = pq.top();
        pq.pop();
        tmp.draw();
    }
}

void Scene::exec()
{
    for(auto& i : actors)
        i.second.exec();
}

double Scene::getPriority()
{
    return render_priority;
}
