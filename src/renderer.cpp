#include "renderer.h"

bool initRenderer(SDL_Window** window, SDL_Renderer** renderer) {
    *window = SDL_CreateWindow(window_Title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        window_Width, window_Height, SDL_WINDOW_SHOWN);

    if (!*window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(*window);
        return false;
    }

    return true;
}

void drawGrid(SDL_Renderer* renderer) {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set line color to white

    int gridSize = 50; // Size of each grid cell
    int windowWidth = window_Width;
    int windowHeight = window_Height;

    // Draw vertical lines
    for (int x = 0; x <= windowWidth; x += gridSize) {
        SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
    }

    // Draw horizontal lines
    for (int y = 0; y <= windowHeight; y += gridSize) {
        SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
    }
}

void drawPlayer(SDL_Renderer* renderer, Player* player) {
    SDL_Rect playerRect;
    playerRect.x = static_cast<int>(player->x);
    playerRect.y = static_cast<int>(player->y);
    playerRect.w = 50; // Width of the player
    playerRect.h = 50; // Height of the player

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set player color to red
    SDL_RenderFillRect(renderer, &playerRect);

    // If you add textures or surfaces here, ensure they are destroyed after use.
}

void updateRenderer(SDL_Renderer* renderer, Player* player) {
    if (!renderer) return;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(renderer);

    // Draw the grid
    drawGrid(renderer);

    // Draw the player
    drawPlayer(renderer, player);

    // Present the renderer (only once per frame)
    SDL_RenderPresent(renderer);
}

void closeRenderer(SDL_Window* window, SDL_Renderer* renderer) {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr; // Avoid dangling pointer
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr; // Avoid dangling pointer
    }
}