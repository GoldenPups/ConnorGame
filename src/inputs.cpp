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
                switch (gameState->cursor) {
                    case 0: // Resume
                        gameState->gameMenu = GAME; // Unpause the game
                        break;
                    case 1: // Options
                        cout << "Load Game" << endl;
                        loadGameState(*gameState); // Load the game state
                        gameState->gameMenu = GAME; // Unpause the game
                        break;
                    case 2: // Save
                        cout << "Save Game" << endl;
                        saveGameState(*gameState); // Save the game state
                        break;
                    case 3: // Quit
                        gameState->gameMenu = MAIN_MENU; // Exit the game
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
                        break;
                    case 1: // "Load", 
                        cout << "Load Game" << endl;
                        loadGameState(*gameState); // Load the game state
                        gameState->gameMenu = GAME; // Unpause the game
                        break;
                    case 2: // "Settings", 
                        cout << "Settings" << endl;
                        
                        break;
                    case 3: // "Quit"
                        gameState->gameMenu = QUIT; // Exit the game
                        break;
                }
                break;
            case SDLK_ESCAPE:
                cout << "ESCAPE" << endl;
                gameState->gameMenu = QUIT; // Exit the game
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
