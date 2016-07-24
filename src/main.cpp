#include "main.hpp"
#include <cstdio>
#include <SDL.h>

int main(int argc, char* argv[])
{
    SDL_Init(0);
    (void)argc;
    (void)argv;
    SDL_Quit();
    return 0;
}
