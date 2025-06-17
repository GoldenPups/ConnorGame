#ifndef SAVE_H
#define SAVE_H

#include "physics.h"

#include <fstream>
#include <string>

// Game 'Menus'
#define GAME 'G'
#define PAUSED 'P'
#define MAIN_MENU 'M'
#define SAVE 'S'
#define QUIT '0'
#define LOAD 'L'
//

struct GameState {
    Player* player;
    char gameMenu; // R:Running, P:Paused, M:Main Menu, 0:Quit
    char prevGameMenu;
    bool wallHacks;

    int cursor; // cursor used for multiple menus, set to zero by default
};

void saveGameState(const GameState& gameState, int slot);
void loadGameState(GameState& gameState, int slot);
void intitializeGameState(GameState* gameState);
char* read_binary_file_as_string(const char* filename);
#endif