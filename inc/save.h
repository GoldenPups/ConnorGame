#ifndef SAVE_H
#define SAVE_H

#include "physics.h"

#include <fstream>
#include <string>

struct GameState {
    bool running;
    Player* player;
    bool paused;
    int pauseMenuCursor; // Cursor position in the pause menu
};

void saveGameState(const GameState& gameState);
void loadGameState(GameState& gameState);
#endif