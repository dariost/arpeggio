#include "Texture.hpp"
#include "GLDebug.hpp"

Texture::Texture(shared_ptr<Logger> logger, uint32_t width, uint32_t height, const vector<uint8_t>& data, string name)
{
    log = logger;
    path = name;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
#ifdef USE_GLDEBUG
    string path_debug = "\"" + path + "\"";
    log->check(path_debug.size() <= 256, true, Logger::Level::CRITICAL, "File path \"", path, "\" is too long");
    fpObjectLabel(GL_TEXTURE, texture_id, path_debug.size(), path_debug.data());
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture_id);
}
