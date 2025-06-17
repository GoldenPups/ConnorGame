#include "save.h"
#include <iostream>

const int startingX = 518;
const int startingY = 229;

void saveGameState(const GameState& gameState, int slot) {
    std::ofstream outFile("assets/bin/saveData" + std::to_string(slot) + ".txt");
    if (outFile.is_open()) {
        outFile << gameState.gameMenu << std::endl;
        outFile << gameState.player->x << " " << gameState.player->y << " "
                << gameState.player->vx << " " << gameState.player->vy << std::endl;
        outFile.close();
    } else {
        std::cerr << "Unable to open file for saving." << std::endl;
    }
}

void loadGameState(GameState& gameState, int slot) {
    std::ifstream inFile("assets/bin/saveData" + std::to_string(slot) + ".txt");
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
    gameState->prevGameMenu = MAIN_MENU; // Initialize previous game menu
    gameState->player = createPlayer(startingX, startingY, 0.0f, 0.0f, playerWidth, playerHeight); // Create a new player object
    gameState->cursor = 0; // Initialize pause menu cursor
}

char* read_binary_file_as_string(const char* filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0'; // Null-terminate the string

    fclose(file);
    return buffer;
}