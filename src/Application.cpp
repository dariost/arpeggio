#include "Application.hpp"

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
    global_config = make_shared<Config>(log);
    log->check(SDL_Init(SDL_INIT_EVERYTHING), 0, Logger::Level::CRITICAL, "Unable to initialize system: ", SDL_GetError());
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
}

Application::~Application()
{
    SDLNet_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
