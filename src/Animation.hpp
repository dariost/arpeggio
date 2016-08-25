#pragma once

#include "global.hpp"

#include "Config.hpp"
#include "Image.hpp"
#include "ImageManager.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

class Animation
{
protected:
    shared_ptr<Logger> log;
    string name;
    array<GLfloat, 16> data;
    Timer timer;
    vector<shared_ptr<Image>> frame;
    double fps;
    size_t getActualFrameNumber();
    GLuint vao;
    GLuint vbo;
    double aspect_ratio;

public:
    Animation(shared_ptr<Logger> logger, const string& anim_name);
    Animation(shared_ptr<Logger> logger, shared_ptr<Config> desc, shared_ptr<ImageManager> image_manager, const string& _name);
    ~Animation();
    void setFrames(const vector<shared_ptr<Image>>& v);
    void setFPS(double f);
    void updateData(const array<GLfloat, 16>& d);
    array<GLfloat, 16> getData();
    void draw();
    void activateTextures(bool toggle = true);
    double getAspectRatio();
};
