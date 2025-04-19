#ifndef INPUTS_H
#define INPUTS_H

#include "physics.h"
#include "renderer.h"

struct GameState {
    bool running;
    Player* player;
    bool paused;
    int pauseMenuCursor; // Cursor position in the pause menu
};

void handleInputs(GameState *gameState, Player* player);


#define MOVEMENT_SCALE 100

#endif