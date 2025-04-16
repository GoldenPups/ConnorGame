#ifndef RENDERER_H
#define RENDERER_H

#define window_Width 650
#define window_Height 500
#define window_Title "Connor Game"

#include <SDL2/SDL.h>
#include <iostream>
#include "physics.h"

// Function declarations
bool initRenderer(SDL_Window** window, SDL_Renderer** renderer);
void drawGrid(SDL_Renderer* renderer);
void drawPlayer(SDL_Renderer* renderer, Player* player);
void updateRenderer(SDL_Renderer* renderer, Player* player);

#endif