#include "Config.hpp"

Config::Config(shared_ptr<Logger> logger, const string& debug_name, const string& rn)
{
    log = logger;
    name = debug_name;
    relative_name = rn;
}

vector<json> Config::getv(const string& obj_name)
{
    log->check(internal.is_object(),
               true,
               Logger::Level::CRITICAL,
               "Error while reading \"",
               obj_name,
               "\" from \"",
               name,
               "\": not an object");
    if(!internal.count(obj_name))
        return vector<json>();
    if(!internal[obj_name].is_array())
    {
        log->log(Logger::Level::ERROR, "Error while reading \"", obj_name, "\" from \"", name, "\": not an array");
        return vector<json>();
    }
    vector<json> tmp;
    for(auto it = internal[obj_name].begin(); it != internal[obj_name].end(); ++it)
        tmp.push_back(*it);
    return tmp;
}

json Config::get_json(const string& obj_name)
{
    log->check(internal.is_object(),
               true,
               Logger::Level::CRITICAL,
               "Error while reading \"",
               obj_name,
               "\" from \"",
               name,
               "\": not an object");
    json tmp;
    try
    {
        tmp = internal[obj_name];
    }
    catch(exception& e)
    {
        log->log(Logger::Level::DEBUG, "Cannot read \"", obj_name, "\" from \"", name, "\": ", e.what(), "; using default value");
        json dummy;
        return dummy;
    }
    return tmp;
}

void Config::parseConfig(shared_ptr<Object> config)
{
    name = config->getName();
    relative_name = config->getRelativeName();
    parseConfig(config->getString());
}

void Config::parseConfig(const string& config)
{
    try
    {
        internal = json::parse(config);
    }
    catch(exception& e)
    {
        log->log(Logger::Level::CRITICAL, "Error while parsing \"", name, "\": ", e.what());
    }
}

string Config::getConfig()
{
    return internal.dump(4);
}

string Config::getName()
{
    return name;
}

string Config::getRelativeName()
{
    return relative_name;
}
