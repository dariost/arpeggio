#pragma once

#include "global.hpp"

class Timer
{
protected:
    chrono::time_point<std::chrono::high_resolution_clock> _initial;
    chrono::time_point<std::chrono::high_resolution_clock> _circle;
    bool _paused;
    double _bias;

public:
    Timer();
    void reset();
    void pause();
    void unpause();
    double getTime();
    void addBias(double b);
};
