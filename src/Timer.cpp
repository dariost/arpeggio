#include "Timer.hpp"

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    _initial = chrono::high_resolution_clock::now();
    _paused = false;
    _bias = 0.0;
}

void Timer::pause()
{
    if(_paused)
        return;
    _paused = true;
    _circle = chrono::high_resolution_clock::now();
}

void Timer::unpause()
{
    if(!_paused)
        return;
    _paused = false;
    _bias -= chrono::duration<double>(std::chrono::high_resolution_clock::now() - _circle).count();
}

double Timer::getTime()
{
    double act_time = chrono::duration<double>(std::chrono::high_resolution_clock::now() - _initial).count();
    act_time += _bias;
    if(_paused)
        act_time -= chrono::duration<double>(std::chrono::high_resolution_clock::now() - _circle).count();
    return act_time;
}

void Timer::addBias(double b)
{
    _bias += b;
}
