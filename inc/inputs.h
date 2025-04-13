#ifndef INPUTS_H
#define INPUTS_H

#include "physics.h"
#include "renderer.h"

void handleInputs(SDL_Event& event, bool &running, Player* player);

#define MOVEMENT_SCALE 100

#endif