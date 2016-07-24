#include "main.hpp"
#include "global.hpp"
#include <SDL.h>

int main(int argc, char* argv[])
{
    SDL_Init(0);
    (void)argc;
    (void)argv;
    #ifdef _WIN32
    glewInit();
    #endif
    glClear(0);
    SDL_Quit();
    return 0;
}
