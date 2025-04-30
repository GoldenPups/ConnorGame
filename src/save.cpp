#include "save.h"
#include <iostream>

void saveGameState(const GameState& gameState) {
    std::ofstream outFile("assets/bin/saveData.txt");
    if (outFile.is_open()) {
        outFile << gameState.gameMenu << std::endl;
        outFile << gameState.player->x << " " << gameState.player->y << " "
                << gameState.player->vx << " " << gameState.player->vy << std::endl;
        outFile.close();
    } else {
        std::cerr << "Unable to open file for saving." << std::endl;
    }
}

void loadGameState(GameState& gameState) {
    std::ifstream inFile("assets/bin/saveData.txt");
    if (inFile.is_open()) {
        inFile >> gameState.gameMenu;
        inFile >> gameState.player->x >> gameState.player->y
                >> gameState.player->vx >> gameState.player->vy;
        inFile.close();
    } else {
        std::cerr << "Unable to open file for loading." << std::endl;
    }
}

void intitializeGameState(GameState* gameState) {
    gameState->gameMenu = MAIN_MENU;
    gameState->player = createPlayer(0.0f, 0.0f, 0.0f, 0.0f, 50, 50); // Create a new player object
    gameState->cursor = 0; // Initialize pause menu cursor
}