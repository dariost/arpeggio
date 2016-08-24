#pragma once

#include "global.hpp"

#include "Config.hpp"
#include "Logger.hpp"

class Scene
{
protected:
    shared_ptr<Logger> log;
    string name;
    shared_ptr<Config> conf;

public:
    Scene(shared_ptr<Logger> logger, string _name, shared_ptr<Config> _conf);
    void activateTextures(bool toggle = true);
    void draw();
    void exec();
    double getPriority();
};
