#include "Animation.hpp"

#include "GLDebug.hpp"

Animation::Animation(shared_ptr<Logger> logger, const string& anim_name)
{
    log = logger;
    name = anim_name;
    fps = 1.0;
    data = {-1.0, -1.0, 0.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0};
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef ARPEGGIO_DEBUG
    string debug_name = "\"" + name + "\"";
    fpObjectLabel(GL_VERTEX_ARRAY, vao, debug_name.size(), debug_name.data());
    fpObjectLabel(GL_BUFFER, vbo, debug_name.size(), debug_name.data());
#endif
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Animation::updateData(const array<GLfloat, 16>& d)
{
    data = d;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(GLfloat), data.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

array<GLfloat, 16> Animation::getData()
{
    return data;
}

void Animation::draw()
{
    frame[getActualFrameNumber()]->bindTexture();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Animation::~Animation()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Animation::setFrames(const vector<shared_ptr<Image>>& v)
{
    log->check(v.size() > 0, true, Logger::Level::CRITICAL, "Trying to feed animation \"", name, "\" with 0 frames");
    for(size_t i = 1; i < v.size(); i++)
    {
        log->check(v[i]->getWidth(),
                   v[i - 1]->getWidth(),
                   Logger::Level::CRITICAL,
                   "In animation \"",
                   name,
                   "\" there is a frame size mismatch");
        log->check(v[i]->getHeight(),
                   v[i - 1]->getHeight(),
                   Logger::Level::CRITICAL,
                   "In animation \"",
                   name,
                   "\" there is a frame size mismatch");
    }
    frame = v;
}

void Animation::setFPS(double f)
{
    log->check(f > 0.0, true, Logger::Level::CRITICAL, "Trying to set non positive FPS in animation \"", name, "\"");
    fps = f;
}

size_t Animation::getActualFrameNumber()
{
    log->check(frame.size() > 0, true, Logger::Level::CRITICAL, "Trying to use empty animation \"", name, "\"");
    return size_t(timer.getTime() / (1.0 / fps)) % frame.size();
}
