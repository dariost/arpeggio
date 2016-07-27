#pragma once

#include "global.hpp"

class Logger
{
public:
    typedef enum { DEBUG = 0, INFO, WARNING, ERROR, CRITICAL } Level;

protected:
    Level verbosity_level;
    void print(Level level, const string& message);
    template <typename T, typename... Args>
    void create_log(stringstream& buffer, const T& arg, Args... args)
    {
        buffer << arg;
        create_log(buffer, args...);
    }
    template <typename T>
    void create_log(stringstream& buffer, const T& arg)
    {
        buffer << arg;
    }
    bool is_tty;

public:
    Logger(Level min_verbosity);
    template <typename... Args>
    void log(Level level, Args... args)
    {
        if(level < verbosity_level)
            return;
        stringstream buffer;
        create_log(buffer, args...);
        print(level, buffer.str());
        if(level == CRITICAL)
            exit(EXIT_FAILURE);
    }
    template <typename T, typename U, typename... Args>
    void check(const T& arg1, const U& arg2, Level level, Args... args)
    {
        if(arg1 == arg2)
            return;
        log(level, args...);
    }
};
