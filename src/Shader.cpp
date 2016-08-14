#include "Shader.hpp"

Shader::Shader(shared_ptr<Logger> logger)
{
    log = logger;
    is_built = false;
    program = glCreateProgram();
}

void Shader::use()
{
    log->check(is_built, true, Logger::Level::CRITICAL, "Trying to use a non compiled shader");
    glUseProgram(program);
}

void Shader::attach(shared_ptr<Object> obj)
{
    string obj_name = obj->getName();
    string ext;
    for(int i = obj_name.size() - 1; i >= 0; i--)
    {
        ext.push_back(obj_name[i]);
        if(obj_name[i] == '.')
            break;
    }
    GLenum type;
    if(ext == "trev.")
        type = GL_VERTEX_SHADER;
    else if(ext == "garf.")
        type = GL_FRAGMENT_SHADER;
    else
        log->log(Logger::Level::CRITICAL, "Cannot deduce type fro shader \"", obj->getName(), "\"");
    attach(obj->getString(), type, obj->getName());
}

void Shader::attach(const char* str, GLenum type, const string& shader_name)
{
    GLuint shdr = glCreateShader(type);
    glShaderSource(shdr, 1, &str, nullptr);
    glCompileShader(shdr);
    GLint status;
    glGetShaderiv(shdr, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        GLint buffer_size;
        glGetShaderiv(shdr, GL_INFO_LOG_LENGTH, &buffer_size);
        log->check(!buffer_size, false, Logger::Level::CRITICAL, "Unknown error while compiling shader \"", shader_name, "\"");
        vector<char> buffer(buffer_size);
        glGetShaderInfoLog(shdr, buffer_size, &buffer_size, buffer.data());
        log->log(Logger::Level::CRITICAL, "Error while compiling shader \"", shader_name, "\": ", buffer.data());
    }
    shader.push_back(shdr);
}

void Shader::compile()
{
    log->check(is_built, false, Logger::Level::CRITICAL, "Trying to build a shader that is already built");
    for(auto& i : shader)
    {
        glAttachShader(program, i);
    }
    glLinkProgram(program);
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE)
    {
        GLint buffer_size;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buffer_size);
        log->check(!buffer_size, false, Logger::Level::CRITICAL, "Unknown error while linking a program");
        vector<char> buffer(buffer_size);
        glGetProgramInfoLog(program, buffer_size, &buffer_size, buffer.data());
        log->log(Logger::Level::CRITICAL, "Error while linking program: ", buffer.data());
    }
    is_built = true;
}

Shader::~Shader()
{
    if(is_built)
        glDeleteProgram(program);
    for(auto& i : shader)
    {
        glDeleteShader(i);
    }
}
