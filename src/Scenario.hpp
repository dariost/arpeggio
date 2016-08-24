#pragma once

#include "global.hpp"

#include "Logger.hpp"
#include "ObjectManager.hpp"
#include "Scene.hpp"

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

public:
    Scenario(shared_ptr<Logger> logger,
             uint32_t _width,
             uint32_t _height,
             const vector<string>& initial_scenes,
             shared_ptr<ObjectManager> om,
             SDL_Window* _window,
             const string& loading_scene_name);
    void exec();
    void draw();
    void add_scene(const string& scene);
    void remove_scene(const string& scene);
};
