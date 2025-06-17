#include "renderer.h"
#include "inputs.h"
#include "world.h"

void drawObstacles(SDL_Renderer* renderer, World* world, int offsetX, int offsetY) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set obstacle color to green
    for (const Object& obstacle : world->obstacles) {
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

void drawOptions(SDL_Renderer *renderer, const std::vector<std::string>& options, int cursor, int yPosition) {
    int optionSpacing = 150; // Space between each option
    int totalWidth = (options.size() - 1) * optionSpacing; // Total width of all options combined
    int startX = (window_Width - totalWidth) / 2; // Calculate starting X position to center the options

    // Draw the menu options
    for (size_t i = 0; i < options.size(); ++i) {
        int optionX = startX + optionSpacing * i; // Calculate the X position for each option
        SDL_Color color = (static_cast<int>(i) == cursor) ? SDL_Color{252, 186, 3, 255} : SDL_Color{255, 255, 255, 255};
        drawText(renderer, options[i].c_str(), optionX, yPosition, 30, 1, color);
    }
}

void PauseMenu(SDL_Renderer *renderer, int cursor) {
    if (!renderer) return;

    // Set the background color for the pause menu
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black 

    const SDL_Rect pausedBar = {0, 0, window_Width, 100};
    SDL_RenderFillRect(renderer, &pausedBar); // Clear the screen

    drawText(renderer, "Paused", window_Width / 2, 20, 50, 1, {255, 255, 255, 255}); // Draw pause text
    drawOptions(renderer, {"Resume", "Load", "Save", "Quit"}, cursor, 70); // Draw options

    // Present the renderer (only once per frame)
    SDL_RenderPresent(renderer);
}

void startScreen(SDL_Renderer *renderer, int cursor) {
    if (!renderer) return;

    // Set the background color for the start screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black 

    const SDL_Rect startBar = {0, 0, window_Width, window_Height};
    SDL_RenderFillRect(renderer, &startBar); // Clear the screen

    drawText(renderer, "Welcome to the Game!", window_Width / 2, window_Height / 2 - 50, 50, 1, {255, 255, 255, 255}); // Draw welcome text
    drawText(renderer, "Press Enter to Start", window_Width / 2, window_Height / 2 + 50, 30, 1, {255, 255, 255, 255}); // Draw instructions

    drawOptions(renderer, {"New Game", "Load", "Settings", "Quit"}, cursor, window_Height / 2 + 100); // Draw options

    // Present the renderer (only once per frame)
    SDL_RenderPresent(renderer);
}

void saveLoadMenu(SDL_Renderer *renderer, int cursor, std::string saveText) {
    if (!renderer) return;

    // Set the background color for the save screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black 

    const SDL_Rect saveBar = {0, 0, window_Width, window_Height};
    SDL_RenderFillRect(renderer, &saveBar); // Clear the screen

    drawText(renderer, saveText.c_str(), window_Width / 2, window_Height / 2 - 50, 50, 1, {255, 255, 255, 255}); // Draw save text
    std::string text = "Press Enter to " + saveText;
    drawText(renderer, text.c_str(), window_Width / 2, window_Height / 2 + 50, 30, 1, {255, 255, 255, 255}); // Draw instructions

    drawOptions(renderer, {"Slot One", "Slot Two", "Slot Three", "Back"}, cursor, window_Height / 2 + 100); // Draw options
    
    // Present the renderer (only once per frame)
    SDL_RenderPresent(renderer);
}

void gameN(SDL_Renderer* renderer, Player* player, World* world, char GameState) {
    if (!renderer) return;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(renderer);

    int offsetX = world -> x;
    int offsetY = world -> y;

    drawObstacles(renderer, world, offsetX, offsetY);

    SDL_SetRenderDrawColor(renderer, 225, 225, 225, 255);

    // Draw the player
    drawPlayer(renderer, player, offsetX, offsetY);
    
    // Draw the player texture
    // drawImage(renderer, playerTexture, static_cast<int>(player->x), static_cast<int>(player->y), 50, 50);
}

void updateRenderer(SDL_Renderer* renderer, GameState* gameState, World* world) {
    if (!renderer || !gameState->player || !world) return;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
    SDL_RenderClear(renderer);

    
    switch (gameState->gameMenu)
    {
        case GAME:
        // Draw the game world and player
        gameN(renderer, gameState->player, world, gameState->gameMenu);
        break;
        case PAUSED:
        // Draw the pause menu
        PauseMenu(renderer, gameState->cursor);
        break;
        case MAIN_MENU:
        // Draw the start screen
        startScreen(renderer, gameState->cursor);
        break;
        case SAVE:
        // Draw the save menu
        saveLoadMenu(renderer, gameState->cursor, "Save");
        break;
        case LOAD:
        // Draw the load menu
        saveLoadMenu(renderer, gameState->cursor, "Load");
        break;
        
        default:
        break;
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}