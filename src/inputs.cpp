#include "inputs.h"

using namespace std;

void handleInputs(GameState *GameState, Player* player) {
    static unordered_set<SDL_Keycode> keysPressed; // Track currently pressed keys
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        keysPressed.insert(event.key.keysym.sym); // Add key to pressed set
        if (event.type == SDL_QUIT) {
            GameState->paused = false;
            GameState->running = false;
        }
        if(GameState->paused){
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        cout << "ESCAPE" << endl;
                        GameState->paused = false; // Unpause the game
                        break;
                    case SDLK_LEFT:
                        cout << "LEFT" << endl;
                        if(GameState->pauseMenuCursor > 0){
                            GameState->pauseMenuCursor--;
                        }
                        break;
                    case SDLK_RIGHT:
                        cout << "RIGHT" << endl;
                        if(GameState->pauseMenuCursor < NUM_PAUSE_MENU_OPTIONS - 1){
                            GameState->pauseMenuCursor++;
                        }
                        break;
                    case SDLK_RETURN:
                        cout << "ENTER" << endl;
                        switch (GameState->pauseMenuCursor) {
                            case 0: // Resume
                                GameState->paused = false; // Unpause the game
                                break;
                            case 1: // Options
                                cout << "Load Game" << endl;
                                loadGameState(*GameState); // Load the game state
                                GameState->paused = false; // Unpause the game
                                break;
                            case 2: // Save
                                cout << "Save Game" << endl;
                                saveGameState(*GameState); // Save the game state
                                break;
                            case 3: // Quit
                                GameState->paused = false; // Unpause the game
                                GameState->running = false; // Exit the game
                                break;
                        }
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                keysPressed.erase(event.key.keysym.sym); // Remove key from pressed set
            }
        } else {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        player->vy = -MOVEMENT_SCALE; // Move up
                        cout << "UP" << endl;
                        break;
                    case SDLK_DOWN:
                        player->vy = MOVEMENT_SCALE; // Move down
                        cout << "DOWN" << endl;
                        break;
                    case SDLK_LEFT:
                        player->vx = -MOVEMENT_SCALE; // Move left
                        cout << "LEFT" << endl;
                        break;
                    case SDLK_RIGHT:
                        player->vx = MOVEMENT_SCALE; // Move right
                        cout << "RIGHT" << endl;
                        break;
                    case SDLK_ESCAPE:
                        cout << "ESCAPE" << endl;
                        GameState->paused = true; // Call pause menu function
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                keysPressed.erase(event.key.keysym.sym); // Remove key from pressed set
    
                // Recalculate velocity based on remaining keys
                if (keysPressed.count(SDLK_UP)) {
                    player->vy = -MOVEMENT_SCALE;
                } else if (keysPressed.count(SDLK_DOWN)) {
                    player->vy = MOVEMENT_SCALE;
                } else {
                    player->vy = 0.0f; // Stop vertical movement
                }
    
                if (keysPressed.count(SDLK_LEFT)) {
                    player->vx = -MOVEMENT_SCALE;
                } else if (keysPressed.count(SDLK_RIGHT)) {
                    player->vx = MOVEMENT_SCALE;
                } else {
                    player->vx = 0.0f; // Stop horizontal movement
                }
            }
        }
        
    }
}