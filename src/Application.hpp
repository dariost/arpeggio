#pragma once

#include "global.hpp"

#include "Logger.hpp"

class Application
{
protected:
    shared_ptr<Logger> log;

public:
    Application(int argc, char** argv);
    ~Application();
};
