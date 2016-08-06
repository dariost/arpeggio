#pragma once

#include "global.hpp"

#include "Logger.hpp"

class Texture
{
protected:
    shared_ptr<Logger> log;
    GLuint texture_id;

public:
    Texture(shared_ptr<Logger> logger, uint32_t width, uint32_t height, const vector<uint8_t>& data);
    void bind();
    ~Texture();
};
