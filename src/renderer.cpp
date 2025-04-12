#include "renderer.h"
#include <iostream>

SDL_Window* window = nullptr;

bool initRenderer() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Connor Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

void closeRenderer() {
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}