#ifndef INPUTS_H
#define INPUTS_H

#include "physics.h"
#include "renderer.h"

struct GameState {
    bool running;
    Player* player;
    bool paused;
};

void handleInputs(GameState *gameState, Player* player);
void handlePauseMenuInputs(GameState *GameState);


#define MOVEMENT_SCALE 100

#endif