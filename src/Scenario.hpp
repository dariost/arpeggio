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

#include "ImageManager.hpp"
#include "Logger.hpp"
#include "ObjectManager.hpp"
#include "Scene.hpp"
#include "Shader.hpp"

class Scenario
{
protected:
    GLuint framebuffer;
    vector<GLuint> texture;
    shared_ptr<Logger> log;
    unordered_map<string, shared_ptr<Scene>> scene;
    shared_ptr<Scene> loading_scene;
    bool is_loading_scene;
    future<unordered_map<string, shared_ptr<Scene>>> future_scenes;
    shared_ptr<ObjectManager> object_manager;
    shared_ptr<ImageManager> image_manager;
    const size_t initial_textures = 32;
    uint32_t width;
    uint32_t height;
    queue<string> to_be_removed;
    queue<string> to_be_added;
    SDL_Window* window;
    void finalize();
    unordered_map<string, shared_ptr<Scene>> load_scenes();
    priority_queue<pair<double, GLuint>> render_queue;
    size_t render_index;
    GLuint vao;
    GLuint vbo;
    unordered_map<string, shared_ptr<Shader>> shader;

public:
    Scenario(shared_ptr<Logger> logger,
             uint32_t _width,
             uint32_t _height,
             const vector<string>& initial_scenes,
             shared_ptr<ObjectManager> om,
             shared_ptr<ImageManager> im,
             SDL_Window* _window,
             const string& loading_scene_name);
    void exec();
    void draw();
    void add_scene(const string& scene);
    void remove_scene(const string& scene);
};
