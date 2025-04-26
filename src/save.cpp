#include "save.h"
#include <iostream>

void saveGameState(const GameState& gameState) {
    std::ofstream outFile("assets/bin/saveData.txt");
    if (outFile.is_open()) {
        outFile << gameState.running << std::endl;
        outFile << gameState.player->x << " " << gameState.player->y << " "
                << gameState.player->vx << " " << gameState.player->vy << std::endl;
        outFile << gameState.paused << std::endl;
        outFile << gameState.pauseMenuCursor << std::endl;
        outFile.close();
    } else {
        std::cerr << "Unable to open file for saving." << std::endl;
    }
}

void loadGameState(GameState& gameState) {
    std::ifstream inFile("assets/bin/saveData.txt");
    if (inFile.is_open()) {
        inFile >> gameState.running;
        inFile >> gameState.player->x >> gameState.player->y
                >> gameState.player->vx >> gameState.player->vy;
        inFile >> gameState.paused;
        inFile >> gameState.pauseMenuCursor;
        inFile.close();
    } else {
        std::cerr << "Unable to open file for loading." << std::endl;
    }
}