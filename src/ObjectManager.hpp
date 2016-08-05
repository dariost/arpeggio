#pragma once

#include "global.hpp"

#include "Logger.hpp"
#include "Object.hpp"

class ObjectManager
{
protected:
    shared_ptr<Logger> log;
    string base_path;
    unordered_map<string, weak_ptr<Object>> bucket;

public:
    ObjectManager(shared_ptr<Logger> logger, const string& path);
    shared_ptr<Object> getObject(const string& file_name,
                                 bool encrypted =
#ifdef ARPEGGIO_DEBUG
                                     false
#else
                                     true
#endif
                                 );
};
