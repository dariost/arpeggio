#include "Application.hpp"

#include "GLDebug.hpp"
#include <SDL_syswm.h>

Application::Application(int argc, char** argv)
{
    should_quit = false;
#ifdef UWP
    string log_output = string(SDL_WinRTGetFSPathUTF8(SDL_WINRT_PATH_LOCAL_FOLDER)) + "/arpeggio_stdout.txt";
    freopen(log_output.c_str(), "w", stdout);
#endif
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
    string base_path = "data/";
    for(uint32_t i = 1; i < (uint32_t)argc; i++)
    {
        if((!strcmp(argv[i], "--base-path") || !strcmp(argv[i], "-p")) && i + 1 < (uint32_t)argc)
        {
            base_path = argv[i + 1];
        }
    }
#ifdef UWP
    base_path = string(SDL_WinRTGetFSPathUTF8(SDL_WINRT_PATH_LOCAL_FOLDER)) + "/";
#endif
    object_manager = make_shared<ObjectManager>(log, base_path);
    global_config = make_shared<Config>(log);
    app_config = make_shared<Config>(log);
    global_config->parseConfig(object_manager->getObject("config.json", false));
    app_config->parseConfig(object_manager->getObject("app.json"));
    unsigned int sdl_init_flags = SDL_INIT_EVERYTHING;
#ifdef __EMSCRIPTEN__
    sdl_init_flags ^= (SDL_INIT_TIMER | SDL_INIT_HAPTIC);
#endif
#ifdef __FreeBSD__
    sdl_init_flags ^= SDL_INIT_HAPTIC;
#endif
    log->check(SDL_Init(sdl_init_flags), 0, Logger::Level::CRITICAL, "Unable to initialize system: ", SDL_GetError());
    log->check(IMG_Init(IMG_INIT_PNG | IMG_INIT_WEBP) & (IMG_INIT_PNG | IMG_INIT_WEBP),
               (int)(IMG_INIT_PNG | IMG_INIT_WEBP),
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
    auto str_or_null = [](const char* s) -> const char* { return s ? s : "NULL"; };
    log->log(Logger::Level::INFO, "Platform: ", str_or_null(SDL_GetPlatform()));
    log->log(Logger::Level::INFO, "SDL_VIDEODRIVER: ", str_or_null(SDL_GetCurrentVideoDriver()));
    log->log(Logger::Level::INFO, "SDL_AUDIODRIVER: ", str_or_null(SDL_GetCurrentAudioDriver()));
    log->log(Logger::Level::INFO, "Number of CPU cores: ", SDL_GetCPUCount());
    log->log(Logger::Level::INFO, "System RAM: ", SDL_GetSystemRAM(), " MiB");
    uint32_t texture_scale_factor = global_config->get("texture_scale_factor", 1U);
    log->check(texture_scale_factor == 1 || texture_scale_factor == 2 || texture_scale_factor == 4 || texture_scale_factor == 8 ||
                   texture_scale_factor == 16,
               true,
               Logger::Level::CRITICAL,
               "Invalid Texture Scale Factor value: ",
               texture_scale_factor);
    image_manager = make_shared<ImageManager>(log, object_manager, texture_scale_factor, max(uint32_t(SDL_GetCPUCount()), 1U));
    uint32_t msaa = global_config->get("msaa", 0U);
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
#ifdef USE_GLDEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
    int fullscreen = global_config->get("fullscreen", 1);
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
        height = global_config->get("height", 600);
    }
    log->log(Logger::Level::INFO, "Window size is ", width, "x", height);
    auto window_mode = SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL;
    if(fullscreen > 0)
        window_mode |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    else if(fullscreen < 0)
        window_mode |= SDL_WINDOW_BORDERLESS;
    window = SDL_CreateWindow(app_config->get("name", string("Arpeggio")).c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              width,
                              height,
                              window_mode);
    log->check(!window, false, Logger::Level::CRITICAL, "Unable to create window: ", SDL_GetError());
    SDL_SysWMinfo wminfo;
    SDL_VERSION(&wminfo.version);
    auto wmret = SDL_GetWindowWMInfo(window, &wminfo);
    log->check(wmret, SDL_TRUE, Logger::Level::WARNING, "Unable to get display server info: ", SDL_GetError());
    auto display_server = SDL_SYSWM_UNKNOWN;
    if(wmret == SDL_TRUE)
    {
        string subsystem;
        display_server = wminfo.subsystem;
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
        log->log(Logger::Level::INFO, "Using display server \"", subsystem, "\"");
    }
    bool show_cursor = global_config->get("show_cursor", false);
    log->check(SDL_ShowCursor(show_cursor ? SDL_ENABLE : SDL_DISABLE) < 0,
               false,
               Logger::Level::ERROR,
               "Cannot change cursor state: ",
               SDL_GetError());
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
    log->check(glewInit(), (unsigned int)GLEW_OK, Logger::Level::CRITICAL, "Cannot get OpenGL function pointers");
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
    GLint max_texture_size;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
    log->log(Logger::Level::INFO, "GL_MAX_TEXTURE_SIZE: ", max_texture_size);
    log->check(max_texture_size >= ARPEGGIO_MAX_TEXTURE_SIZE,
               true,
               Logger::Level::CRITICAL,
               "GL_MAX_TEXTURE_SIZE must be at least ",
               ARPEGGIO_MAX_TEXTURE_SIZE);
#ifdef USE_GLDEBUG
    log->check(SDL_GL_ExtensionSupported("GL_KHR_debug"), SDL_TRUE, Logger::Level::CRITICAL, "GL_KHR_debug is not supported");
    gldebug_init_functions(log);
    glEnable(GL_DEBUG_OUTPUT);
    GLint max_label_length;
    glGetIntegerv(GL_MAX_LABEL_LENGTH, &max_label_length);
    log->log(Logger::Level::INFO, "GL_MAX_LABEL_LENGTH: ", max_label_length);
    log->check(max_label_length >= 256, true, Logger::Level::CRITICAL, "GL_MAX_LABEL_LENGTH is too low");
#endif
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    SDL_GL_GetDrawableSize(window, &real_width, &real_height);
    glViewport(0, 0, real_width, real_height);
    int vsync_default_value = 1;
    if(display_server == SDL_SYSWM_X11 || display_server == SDL_SYSWM_WINDOWS)
        vsync_default_value = -1;
    int vsync = global_config->get("vsync", vsync_default_value);
    if(vsync < 0)
    {
        int vsync_ret = SDL_GL_SetSwapInterval(-1);
        if(vsync_ret)
        {
            log->log(Logger::Level::WARNING, "Cannot use late swap tearing VSync (", SDL_GetError(), "), will use standard VSync");
            log->check(SDL_GL_SetSwapInterval(1), 0, Logger::Level::ERROR, "Cannot enable VSync: ", SDL_GetError());
        }
    }
    else if(vsync > 0)
    {
        log->check(SDL_GL_SetSwapInterval(1), 0, Logger::Level::ERROR, "Cannot enable VSync: ", SDL_GetError());
    }
    else
    {
        log->check(SDL_GL_SetSwapInterval(0), 0, Logger::Level::ERROR, "Cannot disable VSync: ", SDL_GetError());
    }
    auto initial_scenario = app_config->get("initial_scenario", vector<string>());
    auto loading_scene = app_config->get<string>("loading_scene", "");
    scenario =
        make_shared<Scenario>(log, real_width, real_height, initial_scenario, object_manager, image_manager, window, loading_scene);
}

Application::~Application()
{
    scenario.reset();
    SDL_GL_DeleteContext(glcon);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void internal_run(void* _app)
{
    static bool already_reset = false;
    Application* app = (Application*)_app;
    app->scenario->exec();
    app->scenario->draw();
    SDL_Event e;
    while((SDL_PollEvent(&e)))
    {
        if(e.type == SDL_QUIT)
        {
            app->should_quit = true;
        }
#ifdef ARPEGGIO_DEBUG
        else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
        {
            app->should_quit = true;
        }
        else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F5 && !already_reset)
        {
            already_reset = true;
            app->app_config = make_shared<Config>(app->log);
            app->app_config->parseConfig(app->object_manager->getObject("app.json"));
            auto initial_scenario = app->app_config->get("initial_scenario", vector<string>());
            auto loading_scene = app->app_config->get<string>("loading_scene", "");
            auto tmp_scenario = make_shared<Scenario>(app->log,
                                                      app->real_width,
                                                      app->real_height,
                                                      initial_scenario,
                                                      app->object_manager,
                                                      app->image_manager,
                                                      app->window,
                                                      loading_scene);
            app->scenario = tmp_scenario;
        }
        else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_F5)
        {
            already_reset = false;
        }
#endif
    }
    SDL_Delay(0);
}

int Application::run()
{
    while(!should_quit)
    {
        internal_run(this);
    }
    return EXIT_SUCCESS;
}
