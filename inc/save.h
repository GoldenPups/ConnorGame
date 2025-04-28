#ifndef SAVE_H
#define SAVE_H

#include "physics.h"

#include <fstream>
#include <string>

#define GAME 'G'
#define PAUSED 'P'
#define MAIN_MENU 'M'
#define QUIT '0'

struct GameState {
    Player* player;
    char gameMenu; // R:Running, P:Paused, M:Main Menu, 0:Quit

    int pauseMenuCursor; // TODO: GET RID OF THIS!!
};

void saveGameState(const GameState& gameState);
void loadGameState(GameState& gameState);
#endif