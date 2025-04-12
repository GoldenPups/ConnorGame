#include <iostream>
#include "renderer.h"  // Include the renderer header

int main() {
    std::cout << "Hello, World!" << std::endl;
    
    // Initialize and run the renderer
    if (!initRenderer()) {
        return 1;
    }
    
    // Keep the window open for 8 seconds
    SDL_Delay(8000);
    
    // Clean up
    closeRenderer();
    
    return 0;
}