#pragma once

#include "global.hpp"

#include "Object.hpp"

class Shader
{
protected:
    vector<GLuint> shader;
    GLuint program;
    bool is_built;
    shared_ptr<Logger> log;

public:
    Shader(shared_ptr<Logger> logger);
    ~Shader();
    void use();
    void attach(shared_ptr<Object> obj);
    void attach(const char* str, GLenum type, const string& shader_name = "(default)");
    void compile();
};

extern string default_vertex_shader;
extern string default_fragment_shader;
