#ifndef INPUTS_H
#define INPUTS_H

#include "physics.h"
#include "renderer.h"
#include "save.h"
#include <iostream>
#include <unordered_set>

void handleInputs(GameState *gameState, Player* player);
void handlePauseMenuInputs(GameState* GameState, SDL_Event& event);
void handleGameplayInputs(GameState* GameState, Player* player, SDL_Event& event, std::unordered_set<SDL_Keycode>& keysPressed);

#define MOVEMENT_SCALE 100

#endif