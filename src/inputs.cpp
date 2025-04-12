void handleInputs(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    player->vy = -1.0f; // Move up
                    cout << "UP" << endl;
                    break;
                case SDLK_DOWN:
                    player->vy = 1.0f; // Move down
                    cout << "DOWN" << endl;
                    break;
                case SDLK_LEFT:
                    player->vx = -1.0f; // Move left
                    cout << "LEFT" << endl;
                    break;
                case SDLK_RIGHT:
                    player->vx = 1.0f; // Move right
                    cout << "RIGHT" << endl;
                    break;
            }
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN:
                    player->vy = 0.0f; // Stop vertical movement
                    cout << "STOP VERTICAL" << endl;
                    break;
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    player->vx = 0.0f; // Stop horizontal movement
                    cout << "STOP HORIZONTAL" << endl;
                    break;
            }
        }
    }
}