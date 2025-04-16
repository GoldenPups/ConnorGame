#include <iostream>
#include "physics.h"  // Include physics header
#include "renderer.h"  // Include the renderer header
#include "inputs.h"   // Include the inputs header
int main() {
    std::cout << "Hello, World!" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        std::cerr << "SDL Initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "Checkpoint1" << std::endl;
    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    // Initialize and run the renderers
    if (!initRenderer(&window, &renderer)) {
        return 1;
    }
    std::cout << "Checkpoint2" << std::endl;
    // return 0;
    
    // Create a player object
    Player* player = createPlayer(0.0f, 0.0f, 0.0f, 0.0f);
    std::cout << "Checkpoint3" << std::endl;

    bool running = true;
    SDL_Event event;
    std::cout << "Checkpoint4" << std::endl;

    while (running) {
        // Process events
        handleInputs(event, running, player);

        // Update physics
        updatePhysics(player, 0.016f); // Assuming a fixed timestep of 16ms
        
        // Render the grid (or other game elements)
        drawGrid(renderer);
        
        // Update the renderer
        updateRenderer(renderer, player);

        // Delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }

    // Clean up
    destroyPhysics(player);
    std::cout << "Checkpoint5" << std::endl;
    closeRenderer(window, renderer);
    SDL_Quit();
    free(player); // Free the player object
    free(renderer); // Free the renderer object
    free(window); // Free the window object

    return 0;
}