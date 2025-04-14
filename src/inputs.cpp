#include "inputs.h"
#include "renderer.h"
#include <iostream>
#include <unordered_set>

using namespace std;

void handleInputs(SDL_Event& event, bool &running, Player* player) {
    static unordered_set<SDL_Keycode> keysPressed; // Track currently pressed keys

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            keysPressed.insert(event.key.keysym.sym); // Add key to pressed set

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