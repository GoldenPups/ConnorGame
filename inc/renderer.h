#ifndef RENDERER_H
#define RENDERER_H

#define window_Width 650
#define window_Height 500
#define window_Title "Connor Game"

#include <SDL2/SDL.h>
#include <iostream>
#include "physics.h"
#include "world.h"

// Function declarations
bool initRenderer(SDL_Window** window, SDL_Renderer** renderer);
void drawWorld(SDL_Renderer* renderer, World* world, int offsetX, int offsetY);
void drawPlayer(SDL_Renderer* renderer, Player* player, int offsetX, int offsetY);
void updateRenderer(SDL_Renderer* renderer, Player* player, World* world);

#endif