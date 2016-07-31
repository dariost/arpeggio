#include "Application.hpp"

#include "GLDebug.hpp"
#include <SDL_syswm.h>

Application::Application(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    Logger::Level min_verbosity;
#ifdef ARPEGGIO_DEBUG
    min_verbosity = Logger::Level::DEBUG;
#else
    min_verbosity = Logger::Level::INFO;
#endif
    log = make_shared<Logger>(min_verbosity);
#ifdef ARPEGGIO_DEBUG
    log->log(Logger::Level::DEBUG, "Debug mode activated");
#endif
    object_manager = make_shared<ObjectManager>(log);
    global_config = make_shared<Config>(log, "UserConfig");
    app_config = make_shared<Config>(log, "AppConfig");
    global_config->parseConfig(object_manager->getObject("config.json", false)->getString());
    app_config->parseConfig(object_manager->getObject("app.json")->getString());
    unsigned int sdl_init_flags = SDL_INIT_EVERYTHING;
#ifdef __EMSCRIPTEN__
    sdl_init_flags ^= (SDL_INIT_TIMER | SDL_INIT_HAPTIC);
#endif
    log->check(SDL_Init(sdl_init_flags), 0, Logger::Level::CRITICAL, "Unable to initialize system: ", SDL_GetError());
    log->check(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG,
               (int)IMG_INIT_PNG,
               Logger::Level::CRITICAL,
               "Unable to initialize images subsystem: ",
               IMG_GetError());
    log->check(Mix_Init(MIX_INIT_OGG) & MIX_INIT_OGG,
               (int)MIX_INIT_OGG,
               Logger::Level::CRITICAL,
               "Unable to initialize audio subsystem: ",
               Mix_GetError());
    log->check(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024),
               0,
               Logger::Level::CRITICAL,
               "Unable to open the audio device: ",
               Mix_GetError());
    log->check(TTF_Init(), 0, Logger::Level::CRITICAL, "Unable to initialize font subsystem: ", TTF_GetError());
    log->check(SDLNet_Init(), 0, Logger::Level::CRITICAL, "Unable to initialize net subsystem: ", SDLNet_GetError());
    unsigned int msaa = global_config->get("msaa", 0U);
    log->check(msaa == 0 || msaa == 2 || msaa == 4 || msaa == 8 || msaa == 16,
               true,
               Logger::Level::CRITICAL,
               "Invalid MSAA value: ",
               msaa);
    if(msaa != 0)
    {
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, msaa);
    }
#ifdef ARPEGGIO_GLES
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif
#ifdef ARPEGGIO_DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
    bool fullscreen = global_config->get("fullscreen", true);
    unsigned int width, height;
    if(fullscreen)
    {
        SDL_DisplayMode wm;
        log->check(SDL_GetCurrentDisplayMode(0, &wm), 0, Logger::Level::CRITICAL, "Unable to get screen info: ", SDL_GetError());
        width = wm.w;
        height = wm.h;
    }
    else
    {
        width = global_config->get("width", 800);
        height = global_config->get("width", 600);
    }
    log->log(Logger::Level::INFO, "Window size is ", width, "x", height);
    window = SDL_CreateWindow(app_config->get("name", string("Arpeggio")).c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL | ((fullscreen) ? (SDL_WINDOW_FULLSCREEN) : (0)));
    log->check(!window, false, Logger::Level::CRITICAL, "Unable to create window: ", SDL_GetError());
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    auto wmret = SDL_GetWindowWMInfo(window, &wminfo);
    log->check(wmret, SDL_TRUE, Logger::Level::CRITICAL, "Unable to get window manager info: ", SDL_GetError());
    string subsystem;
    switch(wminfo.subsystem)
    {
        case SDL_SYSWM_WINDOWS:
            subsystem = "Microsoft Windows";
            break;
        case SDL_SYSWM_X11:
            subsystem = "X Window System";
            break;
        case SDL_SYSWM_WINRT:
            subsystem = "WinRT";
            break;
        case SDL_SYSWM_DIRECTFB:
            subsystem = "DirectFB";
            break;
        case SDL_SYSWM_COCOA:
            subsystem = "Apple OS X";
            break;
        case SDL_SYSWM_UIKIT:
            subsystem = "UIKit";
            break;
        case SDL_SYSWM_WAYLAND:
            subsystem = "Wayland";
            break;
        case SDL_SYSWM_MIR:
            subsystem = "Mir";
            break;
        case SDL_SYSWM_ANDROID:
            subsystem = "Android";
            break;
        default:
            subsystem = "Unknown";
            break;
    }
    log->log(Logger::Level::INFO, "Using window manager \"", subsystem, "\"");
    glcon = SDL_GL_CreateContext(window);
    log->check(!glcon,
               false,
               Logger::Level::CRITICAL,
               "Cannot create an OpenGL ",
#ifdef ARPEGGIO_GLES
               "ES ",
#endif
               "context: ",
               SDL_GetError());
#ifndef ARPEGGIO_GLES
    log->check(glewInit(), GLEW_OK, Logger::Level::CRITICAL, "Cannot get OpenGL function pointers");
#endif
    auto get_glinfo = [](unsigned int constant) -> const char* {
        auto tmp_info = glGetString(constant);
        if(tmp_info)
            return (const char*)tmp_info;
        return "NULL";
    };
    log->log(Logger::Level::INFO, "GL_VERSION: ", get_glinfo(GL_VERSION));
    log->log(Logger::Level::INFO, "GL_SHADING_LANGUAGE_VERSION: ", get_glinfo(GL_SHADING_LANGUAGE_VERSION));
    log->log(Logger::Level::INFO, "GL_VENDOR: ", get_glinfo(GL_VENDOR));
    log->log(Logger::Level::INFO, "GL_RENDERER: ", get_glinfo(GL_RENDERER));
#ifdef ARPEGGIO_DEBUG
    log->check(SDL_GL_ExtensionSupported("GL_KHR_debug"), SDL_TRUE, Logger::Level::CRITICAL, "GL_KHR_debug is not supported");
    gldebug_init_functions(log);
    glEnable(GL_DEBUG_OUTPUT);
#endif
}

Application::~Application()
{
    SDL_GL_DeleteContext(glcon);
    SDL_DestroyWindow(window);
    SDLNet_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int Application::run()
{
    // TODO: do something
    return EXIT_SUCCESS;
}
