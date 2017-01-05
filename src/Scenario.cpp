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

#include "Scenario.hpp"

#include "GLDebug.hpp"

Scenario::Scenario(shared_ptr<Logger> logger,
                   uint32_t _width,
                   uint32_t _height,
                   const vector<string>& initial_scenes,
                   shared_ptr<ObjectManager> om,
                   shared_ptr<ImageManager> im,
                   SDL_Window* _window,
                   const string& loading_scene_name)
{
    log = logger;
    window = _window;
    object_manager = om;
    image_manager = im;
    width = _width;
    height = _height;
    is_loading_scene = false;
    auto default_shader = make_shared<Shader>(log);
    default_shader->attach(default_vertex_shader.c_str(), GL_VERTEX_SHADER, "default_vertex_shader");
    default_shader->attach(default_fragment_shader.c_str(), GL_FRAGMENT_SHADER, "default_fragment_shader");
    default_shader->compile();
    default_shader->use();
    shader["ARPEGGIO_DEFAULT_SHADER"] = default_shader;
    // VAO and VBO
    vector<GLfloat> data = {-1.0, -1.0, 0.0, 0.0, 1.0, -1.0, 1.0, 0.0, -1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef USE_GLDEBUG
    string vao_debug_name = "\"Scenario VAO\"";
    string vbo_debug_name = "\"Scenario VBO\"";
    fpObjectLabel(GL_VERTEX_ARRAY, vao, vao_debug_name.size(), vao_debug_name.data());
    fpObjectLabel(GL_BUFFER, vbo, vbo_debug_name.size(), vbo_debug_name.data());
#endif
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // Framebuffer and textures
    glGenFramebuffers(1, &framebuffer);
#ifdef USE_GLDEBUG
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    string framebuffer_debug_name = "\"Scenario framebuffer\"";
    fpObjectLabel(GL_FRAMEBUFFER, framebuffer, framebuffer_debug_name.size(), framebuffer_debug_name.data());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
    texture.resize(initial_textures);
    glGenTextures(initial_textures, texture.data());
    for(size_t i = 0; i < initial_textures; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture[i]);
#ifdef USE_GLDEBUG
        string debug_name = "\"Scenario texture #" + to_string(i) + "\"";
        fpObjectLabel(GL_TEXTURE, texture[i], debug_name.size(), debug_name.data());
#endif
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    if(loading_scene_name != "")
    {
        auto obj = object_manager->getObject(string("scenes/") + loading_scene_name + "/scene.json");
        auto conf = make_shared<Config>(log);
        conf->parseConfig(obj);
        auto scn = make_shared<Scene>(log, loading_scene_name, conf, width, height, image_manager, object_manager);
        loading_scene = scn;
        loading_scene->activateTextures();
    }
    log->check(initial_scenes.size() != 0, true, Logger::Level::WARNING, "There are no scenes in the scenario");
    for(const auto& i : initial_scenes)
        to_be_added.push(i);
    finalize();
}

unordered_map<string, shared_ptr<Scene>> Scenario::load_scenes()
{
    unordered_map<string, shared_ptr<Scene>> tmp_ret;
    while(!to_be_added.empty())
    {
        string top = to_be_added.front();
        to_be_added.pop();
        auto obj = object_manager->getObject(string("scenes/") + top + "/scene.json");
        auto conf = make_shared<Config>(log);
        conf->parseConfig(obj);
        auto scn = make_shared<Scene>(log, top, conf, width, height, image_manager, object_manager);
        tmp_ret[top] = scn;
    }
    return tmp_ret;
}

void Scenario::finalize()
{
    auto flush = [&]() -> void {
        while(!to_be_removed.empty())
        {
            scene.erase(to_be_removed.front());
            to_be_removed.pop();
        }
    };
    if(is_loading_scene)
    {
        auto status = future_scenes.wait_for(chrono::microseconds(1));
        if(status == future_status::ready)
        {
            auto ret = future_scenes.get();
            for(auto& i : ret)
            {
                i.second->activateTextures();
                scene[i.first] = i.second;
            }
            flush();
            is_loading_scene = false;
        }
        return;
    }
    if(to_be_added.empty())
    {
        flush();
        return;
    }
    if(loading_scene)
    {
        is_loading_scene = true;
        future_scenes = async(launch::async, [&]() -> auto { return load_scenes(); });
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        SDL_GL_SwapWindow(window);
        auto tmp = load_scenes();
        for(auto& i : tmp)
        {
            i.second->activateTextures();
            scene[i.first] = i.second;
        }
        flush();
    }
}

void Scenario::add_scene(const string& scene)
{
    to_be_added.push(scene);
}

void Scenario::remove_scene(const string& scene)
{
    to_be_removed.push(scene);
}

void Scenario::exec()
{
    if(is_loading_scene)
    {
        loading_scene->exec();
    }
    else
    {
        for(auto& i : scene)
        {
            i.second->exec();
        }
    }
}

void Scenario::draw()
{
    render_index = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    if(is_loading_scene)
    {
        loading_scene->draw();
    }
    else
    {
        for(auto& i : scene)
        {
            log->check(
                render_index < initial_textures, true, Logger::Level::CRITICAL, "Reached scenes limit of ", initial_textures);
            glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
            glBindTexture(GL_TEXTURE_2D, texture[render_index]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture[render_index], 0);
#ifdef ARPEGGIO_DEBUG
            log->check(glCheckFramebufferStatus(GL_FRAMEBUFFER),
                       GLenum(GL_FRAMEBUFFER_COMPLETE),
                       Logger::Level::CRITICAL,
                       "Scenario framebuffer is not properly bound");
#endif
            glClear(GL_COLOR_BUFFER_BIT);
            i.second->draw();
            glFlush();
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            render_queue.push(make_pair(i.second->getPriority(), texture[render_index]));
            render_index++;
        }
    }
    while(!render_queue.empty())
    {
        auto top = render_queue.top();
        render_queue.pop();
        glBindTexture(GL_TEXTURE_2D, top.second);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    glFlush();
    SDL_GL_SwapWindow(window);
    finalize();
}
