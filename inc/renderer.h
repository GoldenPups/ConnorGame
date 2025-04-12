#ifndef RENDERER_H
#define RENDERER_H

#define window_Width 650
#define window_Height 500
#define window_Title "Connor Game"


#include <SDL2/SDL.h>
#include <iostream>

// Function declarations
bool initRenderer();
void closeRenderer();
void drawGrid();

#endif