#include "Config.hpp"

Config::Config(shared_ptr<Logger> logger, const string& debug_name, const string& rn)
{
    log = logger;
    name = debug_name;
    relative_name = rn;
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

string Config::getRelativeName()
{
    return relative_name;
}
