#include <iostream>
#include <SDL.h>      // Include SDL2 header for SDL_Texture and other SDL functions
#include <SDL_image.h> // Include SDL_image header for texture handling
#include "physics.h"  // Include physics header
#include "renderer.h"  // Include the renderer header
#include "inputs.h"   // Include the inputs header
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

    // Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "SDL_image Initialization failed: " << IMG_GetError() << std::endl;
        IMG_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
        printf("Renderer could not be created! Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    
    // Load player texture
    SDL_Texture* playerTexture = loadTextureFromFile(renderer, "assets/textures/player/toddHoward.png"); // Ensure the correct path is passed as a string
    if (!playerTexture) {
        return 1;
    }

    // Create a player object
    Player* player = createPlayer(0.0f, 0.0f, 0.0f, 0.0f);

    bool running = true;

    while (running) {
        // Process events
        handleInputs(running, player);

        // Update physics
        updatePhysics(player, 0.016f); // Assuming a fixed timestep of 16ms

        // Render everything
        updateRenderer(renderer, player, playerTexture);

        // Delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }

    // Clean up
    SDL_DestroyTexture(playerTexture);
    destroyPhysics(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}