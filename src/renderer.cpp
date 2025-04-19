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

void drawText(SDL_Renderer *renderer, const char* text, int x, int y, int fontSize, bool centered, SDL_Color textColor) {
    if (!renderer) return;

    TTF_Font* font = TTF_OpenFont("assets/fonts/Debrosee-ALPnL.ttf", fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (!textSurface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Calculate the text rectangle
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};

    // Center the text on the X coordinate if `centered` is true
    if (centered) {
        textRect.x = x - (textSurface->w / 2); // Adjust X to center the text
    }

    SDL_FreeSurface(textSurface); // Free the surface after creating the texture

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
}

void PauseMenu(SDL_Renderer *renderer, int cursor) {
    if (!renderer) return;

    // Set the background color for the pause menu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black 

    const SDL_Rect pausedBar = {0, 0, window_Width, 100};
    SDL_RenderFillRect(renderer, &pausedBar); // Clear the screen

    drawText(renderer, "Paused", window_Width / 2, 20, 50, 1, {255, 255, 255, 255}); // Draw pause text

    // Draw pause menu text or options here (optional)
    // Options 1-4?
    struct resume {
        int x;
        int y;
    };
    struct options {
        int x;
        int y;
    };
    struct save {
        int x;
        int y;
    };
    struct quit {
        int x;
        int y;
    };

    int optionSpacing = 150; // Space between each option
    int totalWidth = (NUM_PAUSE_MENU_OPTIONS - 1) * optionSpacing; // Total width of all options combined
    int startX = (window_Width - totalWidth) / 2; // Calculate starting X position to center the options

    int OptionsY= 70; // Y position for all options
    resume resume = {startX + optionSpacing * 0, OptionsY};
    options options = {startX + optionSpacing * 1, OptionsY};
    save save = {startX + optionSpacing * 2, OptionsY};
    quit quit = {startX + optionSpacing * 3, OptionsY};

    // Draw the menu options
    drawText(renderer, "Resume", resume.x, resume.y, 30, 1, {255, 255, 255, 255});
    drawText(renderer, "Options", options.x, options.y, 30, 1, {255, 255, 255, 255});
    drawText(renderer, "Save", save.x, save.y, 30, 1, {255, 255, 255, 255});
    drawText(renderer, "Quit", quit.x, quit.y, 30, 1, {255, 255, 255, 255});
    
    switch(cursor){
        case 0:
            drawText(renderer, "Resume", resume.x, resume.y, 30, 1, {252, 186, 3, 255});
            break;
        case 1:
            drawText(renderer, "Options", options.x, options.y, 30, 1, {252, 186, 3, 255});
            break;
        case 2:
            drawText(renderer, "Save", save.x, save.y, 30, 1, {252, 186, 3, 255});
            break;
        case 3:
            drawText(renderer, "Quit", quit.x, quit.y, 30, 1, {252, 186, 3, 255});
            break;
    }

    // Present the renderer (only once per frame)
    SDL_RenderPresent(renderer);
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