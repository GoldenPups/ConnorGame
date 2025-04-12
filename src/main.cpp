#include <iostream>
#include "renderer.h"  // Include the renderer header

void cleanUp(){
    closeRenderer();
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    
    // Initialize and run the renderer
    if (!initRenderer()) {
        return 1;
    }
    
    // Keep the window open for 8 seconds
    SDL_Delay(8000);
    
    cleanUp();
    
    return 0;
}