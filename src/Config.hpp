#pragma once

#include "global.hpp"

#include "Logger.hpp"
#include "Object.hpp"

class Config
{
protected:
    shared_ptr<Logger> log;
    string name;
    string relative_name;
    json internal;

public:
    Config(shared_ptr<Logger> logger, const string& debug_name = "(default)", const string& rn = "NULL");
    string getRelativeName();
    void parseConfig(const string& config);
    void parseConfig(shared_ptr<Object> config);
    string getConfig();
    template <typename T>
    T get(const string& obj_name, const T& default_value = T())
    {
        log->check(internal.is_object(),
                   true,
                   Logger::Level::CRITICAL,
                   "Error while reading \"",
                   obj_name,
                   "\" from \"",
                   name,
                   "\": not an object");
        T tmp;
        try
        {
            tmp = internal[obj_name].get<T>();
        }
        catch(exception& e)
        {
            log->log(
                Logger::Level::DEBUG, "Cannot read \"", obj_name, "\" from \"", name, "\": ", e.what(), "; using default value");
            return default_value;
        }
        return tmp;
    }
    template <typename T>
    void set(const string& obj_name, const T& value = T())
    {
        try
        {
            internal[obj_name] = value;
        }
        catch(exception& e)
        {
            log->log(Logger::Level::CRITICAL, "Cannot write property \"", obj_name, "\" in config \"", name, "\": ", e.what());
        }
    }
};
