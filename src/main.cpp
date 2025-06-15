#include <iostream>
#include <SDL.h>      // Include SDL2 header for SDL_Texture and other SDL functions
#include <SDL_image.h> // Include SDL_image header for texture handling
#include "physics.h"  // Include physics header
#include "renderer.h"  // Include the renderer header
#include "inputs.h"   // Include the inputs header
#include "save.h" // Include the game state header
#include "world.h"   // Include the world header
#include <stdio.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL could not initialize! Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_Window
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

    // Initialize SDL_renderer
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
    
    GameState gameState; // Initialize game state
    intitializeGameState(&gameState);
    // Create a player object
    World* world = createWorld1(100,100);
    Player* player = createPlayer(300, 200, 0, 0, 50, 50); 

    Uint32 lastTime = SDL_GetTicks();
    while (gameState.gameMenu != QUIT) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // Delta time in seconds
        lastTime = currentTime;

        SDL_RenderPresent(renderer);
        
        while(gameState.gameMenu == MAIN_MENU){
            startScreen(renderer, gameState.cursor); // Call start screen function
            handleInputs(&gameState); // Handle start menu inputs
            if(gameState.gameMenu != MAIN_MENU){
                gameState.prevGameMenu = MAIN_MENU; // Save the previous menu state
            }
        }

        // Process events
        handleInputs(&gameState);
        
        while(gameState.gameMenu == PAUSED){
            PauseMenu(renderer, gameState.cursor); // Call pause menu function
            SDL_RenderPresent(renderer); // Present the renderer
            SDL_Delay(100); // Delay to avoid busy waiting
            handleInputs(&gameState);
            if(gameState.gameMenu != PAUSED){
                gameState.cursor = 0;
                gameState.prevGameMenu = PAUSED; // Save the previous menu state
                updateRenderer(renderer, gameState.player, world);
            }
        }

        while(gameState.gameMenu == SAVE){
            saveLoadMenu(renderer, gameState.cursor, "Save"); // Call save screen function
            SDL_RenderPresent(renderer); // Present the renderer
            SDL_Delay(100); // Delay to avoid busy waiting
            handleInputs(&gameState);
            if(gameState.gameMenu != SAVE){
                gameState.cursor = 0;
                gameState.prevGameMenu = SAVE; // Save the previous menu state
                updateRenderer(renderer, gameState.player, world);
            }
        }
        
        while(gameState.gameMenu == LOAD){
            saveLoadMenu(renderer, gameState.cursor, "Load"); // Call save screen function
            SDL_RenderPresent(renderer); // Present the renderer
            SDL_Delay(100); // Delay to avoid busy waiting
            handleInputs(&gameState);
            if(gameState.gameMenu != LOAD){
                gameState.cursor = 0;
                gameState.prevGameMenu = LOAD; // Save the previous menu state
                updateRenderer(renderer, gameState.player, world);
            }
        }

        updatePhysics(gameState.player, world, deltaTime); // Pass deltaTime
        
        // Check for events
        checkEvents(gameState.player, world);
        
        // Update the renderer
        // display a black frame if in menus
        if(gameState.gameMenu != GAME){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
            SDL_RenderClear(renderer); // Clear the screen
        } else {
            updateRenderer(renderer, gameState.player, world);
        }

        // Delay to control frame rate
        SDL_Delay(8);
        std::cout << gameState.player->vx << " " << gameState.player->vy << " dt: " << deltaTime << std::endl; // Debug output
    }

    // Clean up
    SDL_DestroyTexture(playerTexture);
    destroyPhysics(gameState.player);
    destroyWorld(world);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();

    return 0;
}