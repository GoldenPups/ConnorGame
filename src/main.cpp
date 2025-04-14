#include <iostream>
#include <SDL.h>      // Include SDL2 header for SDL_Texture and other SDL functions
#include <SDL_image.h> // Include SDL_image header for texture handling
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

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image Initialization failed: " << IMG_GetError() << std::endl;
        IMG_Quit();
        cleanUp();
        return 1;
    }

    // Load player texture
    SDL_Texture* playerTexture = loadTextureFromFile("assets/todd-howard/toddHoward.jpg"); // Ensure the correct path is passed as a string
    if (!playerTexture) {
        cleanUp();
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
        
        // Draw the player texture
        drawImage(playerTexture, player->x, player->y, 50, 50); // Use preloaded texture
        updateRenderer(player);

        // Delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }

    // Clean up
    SDL_DestroyTexture(playerTexture);
    destroyPhysics(player);
    cleanUp();

    return 0;
}