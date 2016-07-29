#pragma once

#include "global.hpp"

#include "Logger.hpp"

class Object
{
protected:
    vector<uint8_t> data;
    shared_ptr<Logger> log;
    string name;

public:
    size_t getSize();
    void* getData();
    const char* getString();
    Object(shared_ptr<Logger> logger,
           const string& file_name,
           bool crypted =
#ifdef ARPEGGIO_DEBUG
               false
#else
               true
#endif
           );
};
