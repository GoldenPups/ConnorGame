#include "renderer.h"

void drawWorld(SDL_Renderer* renderer, World* world) {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set line color to white

    int offsetX = world -> x;
    int offsetY = world -> y;
    int worldWidth = world -> width;
    int worldHeight = world -> height;
    int gridSize = 50; // Size of each grid cell
    int worldTop = -offsetY;
    int worldBottom = worldHeight - offsetY;
    int worldLeft = -offsetX;
    int worldRight = worldWidth - offsetX;

    // Draw vertical lines
    for (int x = worldLeft; x <= worldRight; x += gridSize) {
        SDL_RenderDrawLine(renderer, x, worldTop, x, worldBottom);
    }

    // Draw horizontal lines
    for (int y = worldTop; y <= worldBottom; y += gridSize) {
        SDL_RenderDrawLine(renderer, worldLeft, y, worldRight, y);
    }
}

void drawPlayer(SDL_Renderer* renderer, Player* player) {
    SDL_Rect playerRect;
    playerRect.x = static_cast<int>(player->x);
    playerRect.y = static_cast<int>(player->y);
    playerRect.w = player->width; // Width of the player
    playerRect.h = player->height; // Height of the player

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set player color to red
    SDL_RenderFillRect(renderer, &playerRect);
}

void updateRenderer(SDL_Renderer* renderer, Player* player, World* world) {
    if (!renderer) return;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(renderer);

    // Draw the grid
    drawWorld(renderer, world);

    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);

    // Draw the player
    drawPlayer(renderer, player);
    
    SDL_RenderPresent(renderer);
}