#pragma once

#include "global.hpp"

#include "Image.hpp"
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

public:
    Animation(shared_ptr<Logger> logger, const string& anim_name);
    ~Animation();
    void setFrames(const vector<shared_ptr<Image>>& v);
    void setFPS(double f);
    void updateData(const array<GLfloat, 16>& d);
    array<GLfloat, 16> getData();
    void draw();
};
