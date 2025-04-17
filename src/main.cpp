#include <iostream>
#include "physics.h"  // Include physics header
#include "renderer.h"  // Include the renderer header
#include "inputs.h"   // Include the inputs header
#include "world1.h"   // Include the world header
#include <stdio.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Connor-Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                            window_Width, window_Height, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        printf("Renderer could not be created! Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Create a player object
    World* world = createWorld();
    Player* player = createPlayer(-world->x + 50, -world->y + 50, 0, 0, 50, 50); 

    bool running = true;

    while (running) {
        // Process events
        handleInputs(running, player);

        // Update physics
        updatePhysics(player, world, 0.016f); // Assuming a fixed timestep of 16ms

        // Update the renderer
        updateRenderer(renderer, player, world);

        // Delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }

    // Clean up
    destroyPhysics(player);
    destroyWorld(world);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}