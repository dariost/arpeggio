#pragma once

#include "global.hpp"

#include "Logger.hpp"
#include "Object.hpp"
#include "Texture.hpp"

class Image
{
protected:
    shared_ptr<Logger> log;
    string path;
    uint32_t width;
    uint32_t height;
    vector<uint8_t> data;
    shared_ptr<Texture> texture;

public:
    Image(shared_ptr<Logger> logger, shared_ptr<Object> obj, uint32_t scale_factor);
    uint32_t getWidth();
    uint32_t getHeight();
    void* getData();
    string getName();
    bool isTextureActive();
    void activateTexture(bool toggle = true);
    void bindTexture();
};
