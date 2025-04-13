#include <iostream>
#include "physics.h"  // Include physics header
#include "renderer.h"  // Include the renderer header
#include "inputs.h"   // Include the inputs header

void cleanUp() {
    closeRenderer();
    SDL_Quit();
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize and run the renderers
    if (!initRenderer()) {
        return 1;
    }

    // Create a player object
    Player* player = createPlayer(0.0f, 0.0f, 0.0f, 0.0f);

    bool running = true;
    SDL_Event event;

    while (running) {
        // Process events
        handleInputs(event, running, player);

        // Update physics
        updatePhysics(player, 0.016f); // Assuming a fixed timestep of 16ms
        
        // Render the grid (or other game elements)
        drawGrid();
        
        // Update the renderer
        updateRenderer(player);

        // Delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }

    // Clean up
    destroyPhysics(player);
    cleanUp();

    return 0;
}