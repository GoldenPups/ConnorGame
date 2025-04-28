#ifndef RENDERER_H
#define RENDERER_H

#define window_Width 650
#define window_Height 500
#define window_Title "Connor Game"
#define NUM_PAUSE_MENU_OPTIONS 4


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "physics.h"

// Function declarations
bool initRenderer(SDL_Window** window, SDL_Renderer** renderer);
void drawGrid(SDL_Renderer* renderer);
void drawPlayer(SDL_Renderer* renderer, Player* player);
void updateRenderer(SDL_Renderer* renderer, Player* player, SDL_Texture* playerTexture);
SDL_Texture* loadTextureFromFile(SDL_Renderer *renderer, const char* filePath);
void drawImage(SDL_Renderer *renderer, SDL_Texture* texture, int x, int y, int width, int height);
void PauseMenu(SDL_Renderer *renderer, int cursor);
void startScreen(SDL_Renderer *renderer);

#endif