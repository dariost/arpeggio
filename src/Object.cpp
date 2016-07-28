#include "Object.hpp"

Object::Object(shared_ptr<Logger> logger, const string& file_name, bool crypted)
{
    log = logger;
    name = file_name;
    (void)crypted;
#ifndef ARPEGGIO_DEBUG
#warning Implement file encryption
#endif
    log->check(crypted, false, Logger::Level::CRITICAL, "File encryption is not implemented yet");
    errno = 0;
    FILE* in = fopen(name.c_str(), "rb");
    log->check(!in, false, Logger::Level::CRITICAL, "Cannot open \"", name, "\": ", strerror(errno));
    uint8_t buffer[4096];
    while(!feof(in))
    {
        size_t ret = fread(buffer, 1, 4096, in);
        if(ret == 0)
            break;
        data.insert(data.end(), buffer, buffer + ret);
    }
    fclose(in);
    data.push_back(0);
}

size_t getSize()
{
    return data.size() - 1;
}

void* getData()
{
    return (void*)data.data();
}

const char* getString()
{
    return (const char*)data.data();
}
