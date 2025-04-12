#ifndef RENDERER_H
#define RENDERER_H

#define window_Width 650
#define window_Height 500
#define window_Title "Connor Game"


#include <SDL2/SDL.h>
#include <iostream>
#include "physics.h"

// Function declarations
bool initRenderer();
void closeRenderer();
void drawGrid();
void drawPlayer(Player* player);
void updateRenderer(Player* player);

#endif