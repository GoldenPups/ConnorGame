#include "renderer.h"
#include <SDL2/SDL_image.h>

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

SDL_Texture* loadTextureFromFile(SDL_Renderer *renderer, const char* filePath) {
    SDL_Surface* imageSurface = IMG_Load(filePath); // loadTextureFromFile
    if (!imageSurface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }
    return texture;
}

void drawImage(SDL_Renderer *renderer, SDL_Texture* texture, int x, int y, int width, int height) {
    if (!renderer || !texture) return;

    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}

void updateRenderer(SDL_Renderer *renderer, Player* player, SDL_Texture* playerTexture) {
    if (!renderer) return;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(renderer);

    // Draw the grid
    drawGrid(renderer);
    
    // Draw the player (optional, if you want a rectangle overlay)
    drawPlayer(renderer, player);
    
    // Draw the player texture
    drawImage(renderer, playerTexture, static_cast<int>(player->x), static_cast<int>(player->y), 50, 50);
    
    // Present the renderer (only once per frame)
    SDL_RenderPresent(renderer);
}