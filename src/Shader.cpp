#include "Shader.hpp"

#include "GLDebug.hpp"

Shader::Shader(shared_ptr<Logger> logger)
{
    log = logger;
    is_built = false;
    program = glCreateProgram();
#ifdef USE_GLDEBUG
    string program_name = "\"Linked Shader\"";
    fpObjectLabel(GL_PROGRAM, program, program_name.size(), program_name.data());
#endif
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
    reverse(ext.begin(), ext.end());
    GLenum type = 0;
    if(ext == ".vert")
        type = GL_VERTEX_SHADER;
    else if(ext == ".frag")
        type = GL_FRAGMENT_SHADER;
    else
        log->log(Logger::Level::CRITICAL, "Cannot deduce type from shader \"", obj->getName(), "\"");
    attach(obj->getString(), type, obj->getName());
}

void Shader::attach(const char* str, GLenum type, const string& shader_name)
{
    GLuint shdr = glCreateShader(type);
#ifdef USE_GLDEBUG
    string shader_name_debug = "\"" + shader_name + "\"";
    fpObjectLabel(GL_SHADER, shdr, shader_name_debug.size(), shader_name_debug.data());
#endif
    string true_shader;
#if defined(ARPEGGIO_GLES) || defined(__HAIKU__)
    true_shader += "#version 300 es\n";
    true_shader += "precision mediump float;\n";
#else
    true_shader += "#version 330 core\n";
#endif
    true_shader += str;
    const char* s = (const char*)true_shader.data();
    glShaderSource(shdr, 1, &s, nullptr);
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

string default_vertex_shader = R"delim(
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 texPos;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);
    texCoord = texPos;
}
)delim";
string default_fragment_shader = R"delim(
in vec2 texCoord;

out vec4 color;

uniform sampler2D uniformTexture;

void main()
{
    color = texture(uniformTexture, texCoord);
}
)delim";
