#include "renderer.h"

void drawWorld(SDL_Renderer* renderer, World* world, int offsetX, int offsetY) {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set line color to white

    int worldWidth = world -> width;
    int worldHeight = world -> height;
    int gridSize = 50; // Size of each grid cell
    int worldTop = offsetY;
    int worldBottom = worldHeight + offsetY;
    int worldLeft = offsetX;
    int worldRight = worldWidth + offsetX;

    // Draw vertical lines
    for (int x = worldLeft; x <= worldRight; x += gridSize) {
        SDL_RenderDrawLine(renderer, x, worldTop, x, worldBottom);
    }

    // Draw horizontal lines
    for (int y = worldTop; y <= worldBottom; y += gridSize) {
        SDL_RenderDrawLine(renderer, worldLeft, y, worldRight, y);
    }
}

void drawObstacles(SDL_Renderer* renderer, World* world, int offsetX, int offsetY) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set obstacle color to green
    for (const Obstacle& obstacle : world->obstacles) {
        SDL_Rect rect = {obstacle.x + offsetX, obstacle.y + offsetY, obstacle.width, obstacle.height};
        SDL_RenderFillRect(renderer, &rect);
    }
}


void drawPlayer(SDL_Renderer* renderer, Player* player, int offsetX, int offsetY) {
    SDL_Rect playerRect;
    playerRect.x = static_cast<int>(player->x) + offsetX;
    playerRect.y = static_cast<int>(player->y) + offsetY;
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

    int offsetX = world -> x;
    int offsetY = world -> y;

    // Draw the grid
    drawWorld(renderer, world, offsetX, offsetY);
    drawObstacles(renderer, world, offsetX, offsetY);

    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);

    // Draw the player
    drawPlayer(renderer, player, offsetX, offsetY);
    
    SDL_RenderPresent(renderer);
}