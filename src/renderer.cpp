#include "renderer.h"

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
}

void updateRenderer(SDL_Renderer* renderer, Player* player) {
    if (!renderer) return;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(renderer);

    // Draw the grid
    // drawGrid(renderer);

    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255); // Set background color to black
    SDL_RenderDrawLine(renderer, 0, window_Height / 2, window_Width, window_Height / 2); // Horizontal line

    // Draw the player
    // drawPlayer(player);
    
    SDL_RenderPresent(renderer);
}