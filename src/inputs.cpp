#include "inputs.h"
#include "physics.h"
#include "renderer.h"
#include "save.h"

using namespace std;

void handleInputs(GameState* gameState) {
    static unordered_set<SDL_Keycode> keysPressed; // Track currently pressed keys
    SDL_Event event;

    // Centralized event polling
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameState->gameMenu = QUIT; // Set game state to quit
            return;
        }
        switch(gameState->gameMenu) {
            case MAIN_MENU:
                handleStartMenuInputs(gameState, event); // Handle start menu inputs
                break;
            case GAME:
                handleGameplayInputs(gameState, event, keysPressed); // Handle gameplay inputs
                break;
            case PAUSED:
                keysPressed.clear(); // Clear pressed keys
                gameState->player->vx, gameState->player->vy = 0.0f; // Reset player movement
                handlePauseMenuInputs(gameState, event); // Handle pause menu inputs
                break;
            case SAVE:
                keysPressed.clear(); // Clear pressed keys
                gameState->player->vx, gameState->player->vy = 0.0f; // Reset player movement
                handleSaveMenuInputs(gameState, event); // Handle pause menu inputs
                break;
            case LOAD:
                keysPressed.clear(); // Clear pressed keys
                gameState->player->vx, gameState->player->vy = 0.0f; // Reset player movement
                handleLoadMenuInputs(gameState, event); // Handle pause menu inputs
                break;
        }
    }
}

void handleGameplayInputs(GameState* gameState, SDL_Event& event, unordered_set<SDL_Keycode>& keysPressed) {
    if (event.type == SDL_KEYDOWN) {
        keysPressed.insert(event.key.keysym.sym); // Add key to pressed set
        switch (event.key.keysym.sym) {
            case SDLK_UP:
                gameState->player->vy = -MOVEMENT_SCALE; // Move up
                // cout << "UP" << endl;
                break;
            case SDLK_DOWN:
                gameState->player->vy = MOVEMENT_SCALE; // Move down
                // cout << "DOWN" << endl;
                break;
            case SDLK_LEFT:
                gameState->player->vx = -MOVEMENT_SCALE; // Move left
                // cout << "LEFT" << endl;
                break;
            case SDLK_RIGHT:
                gameState->player->vx = MOVEMENT_SCALE; // Move right
                // cout << "RIGHT" << endl;
                break;
            case SDLK_ESCAPE:
                // cout << "ESCAPE" << endl;
                gameState->gameMenu = PAUSED; // Pause the game
                break;
        }
        cout << gameState->player->vx << " " << gameState->player->vy << endl; // Debug output
    } else if (event.type == SDL_KEYUP) {
        keysPressed.erase(event.key.keysym.sym); // Remove key from pressed set

        // Recalculate velocity based on remaining keys
        if (keysPressed.count(SDLK_UP)) {
            gameState->player->vy = -MOVEMENT_SCALE;
        } else if (keysPressed.count(SDLK_DOWN)) {
            gameState->player->vy = MOVEMENT_SCALE;
        } else {
            gameState->player->vy = 0.0f; // Stop vertical movement
        }

        if (keysPressed.count(SDLK_LEFT)) {
            gameState->player->vx = -MOVEMENT_SCALE;
        } else if (keysPressed.count(SDLK_RIGHT)) {
            gameState->player->vx = MOVEMENT_SCALE;
        } else {
            gameState->player->vx = 0.0f; // Stop horizontal movement
        }
    }
}

void handlePauseMenuInputs(GameState* gameState, SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                // cout << "ESCAPE" << endl;
                gameState->gameMenu = GAME; // Unpause the game
                gameState->prevGameMenu = PAUSED;
                gameState->cursor = 0;
                break;
            case SDLK_LEFT:
                // cout << "LEFT" << endl;
                if (gameState->cursor > 0) {
                    gameState->cursor--;
                }
                break;
            case SDLK_RIGHT:
                // cout << "RIGHT" << endl;
                if (gameState->cursor < NUM_PAUSE_MENU_OPTIONS - 1) {
                    gameState->cursor++;
                }
                break;
            case SDLK_RETURN:
                // cout << "ENTER" << endl;
                gameState->prevGameMenu = PAUSED;
                switch (gameState->cursor) {
                    case 0: // Resume
                        gameState->gameMenu = GAME; // Unpause the game
                        gameState->cursor = 0;
                        break;
                    case 1: // LOAD
                        cout << "Load Game" << endl;
                        gameState->gameMenu = LOAD; // Unpause the game
                        gameState->cursor = 0;
                        break;
                    case 2: // Save
                        cout << "Save Game" << endl;
                        gameState->gameMenu = SAVE; // Save the game state
                        gameState->cursor = 0;
                        break;
                    case 3: // Quit
                        gameState->gameMenu = MAIN_MENU; // Exit the game
                        gameState->cursor = 0;
                        break;
                }
                break;
        }
    }
}

void handleStartMenuInputs(GameState* gameState, SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                switch (gameState->cursor) {
                    case 0: // "New Game", 
                        intitializeGameState(gameState); // Initialize a new game state
                        gameState->gameMenu = GAME; // Unpause the game
                        gameState->prevGameMenu = MAIN_MENU;
                        gameState->cursor = 0; 
                        break;
                    case 1: // "Load", 
                        cout << "Load Game" << endl;
                        gameState->gameMenu = LOAD; // Unpause the game
                        gameState->prevGameMenu = MAIN_MENU;
                        gameState->cursor = 0;
                        break;
                    case 2: // "Settings", 
                        cout << "Settings" << endl;
                        gameState->prevGameMenu = MAIN_MENU;
                        gameState->cursor = 0;
                        
                        break;
                    case 3: // "Quit"
                        gameState->gameMenu = QUIT; // Exit the game
                        break;
                }
                break;
            case SDLK_ESCAPE:
                cout << "ESCAPE" << endl;
                gameState->gameMenu = QUIT; // Exit the game
                gameState->cursor = 0;
                break;
            case SDLK_LEFT:
                // cout << "LEFT" << endl;
                if (gameState->cursor > 0) {
                    gameState->cursor--;
                }
                break;
            case SDLK_RIGHT:
                // cout << "RIGHT" << endl;
                if (gameState->cursor < NUM_MAIN_MENU_OPTIONS - 1) {
                    gameState->cursor++;
                }
                break;
        }
    }
}

void handleSaveMenuInputs(GameState* gameState, SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                switch (gameState->cursor) {
                    case 0: // Save Slot 1
                        cout << "Save Slot 1" << endl;
                        saveGameState(*gameState, 0); // Save the game state
                        break;
                    case 1: // Save Slot 2
                        cout << "Save Slot 2" << endl;
                        saveGameState(*gameState, 1); // Save the game state
                        break;
                    case 2: // Save Slot 3
                        cout << "Save Slot 3" << endl;
                        saveGameState(*gameState, 2); // Save the game state
                        break;
                    case 3: // Back
                        gameState->gameMenu = gameState->prevGameMenu; // Go back to previous menu
                        break;
                }
                break;
            case SDLK_ESCAPE:
                cout << "ESCAPE" << endl;
                gameState->gameMenu = gameState->prevGameMenu; // Go back to previous menu
                break;
            case SDLK_LEFT:
                // cout << "LEFT" << endl;
                if (gameState->cursor > 0) {
                    gameState->cursor--;
                }
                break;
            case SDLK_RIGHT:
                // cout << "RIGHT" << endl;
                if (gameState->cursor < NUM_MAIN_MENU_OPTIONS - 1) {
                    gameState->cursor++;
                }
                break;
        }
    }
}

void handleLoadMenuInputs(GameState* gameState, SDL_Event& event) {
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_RETURN:
                switch (gameState->cursor) {
                    case 0: // Load Slot 1
                        cout << "Load Slot 1" << endl;
                        loadGameState(*gameState, 0); // Load the game state
                        gameState->gameMenu = GAME; // Unpause the game
                        gameState->prevGameMenu = LOAD;
                        gameState->cursor = 0;
                        break;
                    case 1: // Load Slot 2
                        cout << "Load Slot 2" << endl;
                        loadGameState(*gameState, 1); // Load the game state
                        gameState->gameMenu = GAME; // Unpause the game
                        gameState->prevGameMenu = LOAD;
                        gameState->cursor = 0;
                        break;
                    case 2: // Load Slot 3
                        cout << "Load Slot 3" << endl;
                        loadGameState(*gameState, 2); // Load the game state
                        gameState->gameMenu = GAME; // Unpause the game
                        gameState->prevGameMenu = LOAD;
                        gameState->cursor = 0;
                        break;
                    case 3: // Back
                        gameState->gameMenu = gameState->prevGameMenu; // Go back to previous menu
                        break;
                }
                break;
            case SDLK_ESCAPE:
                cout << "ESCAPE" << endl;
                gameState->gameMenu = gameState->prevGameMenu; // Go back to previous menu
                gameState->cursor = 0;
                break;
            case SDLK_LEFT:
                // cout << "LEFT" << endl;
                if (gameState->cursor > 0) {
                    gameState->cursor--;
                }
                break;
            case SDLK_RIGHT:
                // cout << "RIGHT" << endl;
                if (gameState->cursor < NUM_MAIN_MENU_OPTIONS - 1) {
                    gameState->cursor++;
                }
                break;
        }
    }
}