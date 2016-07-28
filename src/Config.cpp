#include "Config.hpp"

Config::Config(shared_ptr<Logger> logger, const string& debug_name)
{
    log = logger;
    name = debug_name;
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
