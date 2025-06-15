#include "physics.h"
#include "world.h"
#include "renderer.h"

Player* createPlayer(float x, float y, float vx, float vy, int width, int height) {
    Player* player = new Player;
    player->x = x;
    player->y = y;
    player->vx = vx;
    player->vy = vy;
    player->width = width;
    player->height = height;
    return player;
}

void setPosPlayer(Player* player, float x, float y) {
    player->x = x;
    player->y = y;
}
void setVelPlayer(Player* player, float vx, float vy) {
    player->vx = vx;
    player->vy = vy;
}

bool checkCollision(Player* player, Object* object) {
    return !(player->x + player->width < object->x ||  // Player is to the left of the obstacle
             player->x > object->x + object->width || // Player is to the right of the obstacle
             player->y + player->height < object->y ||  // Player is above the obstacle
             player->y > object->y + object->height); // Player is below the obstacle
}

const float SPEED = 200; // Speed multiplier for movement
const int ITTERATIONS = 10; // Number of iterations for smoother movement

void updatePhysics(Player* player, World* world, float deltaTime) {
    for(int i = 0; i < ITTERATIONS; i++){
        float speedMultiplier = deltaTime * SPEED/ITTERATIONS;
        player->x += (player->vx) * speedMultiplier;
        player->y += (player->vy) * speedMultiplier;

        int startOffset = 25; //start scolling 50 pixels of edge
        int offsetX = world->x;
        int offsetY = world->y;

        // Check for window boundaries
        int maxX = window_Width - player->width - startOffset;
        int maxY = window_Height - player->height - startOffset;
        int minX = startOffset;
        int minY = startOffset;

        //Scroll the world if the player is close to the edges
        if(player->x + offsetX > maxX) {
            world->x -= player->x + offsetX - maxX;
        } else if(player->x + offsetX < minX) {
            world->x -= player->x + offsetX - minX;
        }
        if(player->y + offsetY > maxY) {
            world->y -= player->y + offsetY - maxY;
        } else if(player->y + offsetY < minY) {
            world->y -= player->y + offsetY - minY;
        }

        // Check for collision with world boundaries
        for (Object& obstacle : world->obstacles) {
            if (checkCollision(player, &obstacle)) {
                // Handle collision (e.g., stop movement or adjust position)
                player->x -= player->vx * speedMultiplier;
                player->y -= player->vy * speedMultiplier;
                break; // Exit the loop after handling the first collision
            }
        }
    }
}

void checkEvents(Player* player, World* world) {
    for (Object& event : world->events) {
        if (checkCollision(player, &event)) {
           event.eventFunc(); // Call the event function
        }
    }
}

void destroyPhysics(Player* player) {
    delete player;
}