#pragma once

#include "global.hpp"

#include "Config.hpp"
#include "ImageManager.hpp"
#include "Logger.hpp"
#include "ObjectManager.hpp"

class Application
{
protected:
    shared_ptr<Logger> log;
    shared_ptr<Config> global_config;
    shared_ptr<Config> app_config;
    shared_ptr<ObjectManager> object_manager;
    shared_ptr<ImageManager> image_manager;
    SDL_Window* window;
    SDL_GLContext glcon;

public:
    Application(int argc, char** argv);
    ~Application();
    int run();
};
