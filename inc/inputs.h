#ifndef INPUTS_H
#define INPUTS_H

#include <iostream>
#include <unordered_set>
#include "inputs.h"
#include "physics.h"
#include "renderer.h"
#include "save.h"

void handleInputs(GameState *gameState);
void handlePauseMenuInputs(GameState* GameState, SDL_Event& event);
void handleGameplayInputs(GameState* GameState, SDL_Event& event, std::unordered_set<SDL_Keycode>& keysPressed);
void handleStartMenuInputs(GameState* gameState, SDL_Event& event);

#define MOVEMENT_SCALE 100

#define NUM_PAUSE_MENU_OPTIONS 4
#define NUM_MAIN_MENU_OPTIONS 4

#endif