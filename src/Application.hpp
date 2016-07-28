#pragma once

#include "global.hpp"

#include "Config.hpp"
#include "Logger.hpp"

class Application
{
protected:
    shared_ptr<Logger> log;
    shared_ptr<Config> global_config;

public:
    Application(int argc, char** argv);
    ~Application();
};
