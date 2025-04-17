#include "physics.h"
#include "world1.h"
#include "renderer.h"

Player* createPlayer(int x, int y, float vx, float vy, int width, int height) {
    Player* player = new Player;
    player->x = x;
    player->y = y;
    player->vx = vx;
    player->vy = vy;
    player->width = width;
    player->height = height;
    return player;
}

bool checkCollision(Player* player, Obstacle* obstacle) {
    return !(player->x + player->width < obstacle->x ||  // Player is to the left of the obstacle
             player->x > obstacle->x + obstacle->width || // Player is to the right of the obstacle
             player->y + player->height < obstacle->y ||  // Player is above the obstacle
             player->y > obstacle->y + obstacle->height); // Player is below the obstacle
}

void updatePhysics(Player* player, World* world, float dt) {
    player->x += static_cast<int>(player->vx * dt);
    player->y += static_cast<int>(player->vy * dt);

    int offsetX = world->x;
    int offsetY = world->y;

    // Check for window boundaries
    int maxX = window_Width - player->width;
    int maxY = window_Height - player->height;
    int minX = 0;
    int minY = 0;

    if(player->x + offsetX > maxX) {
        world->x += player->x - maxX;
    } else if(player->x + offsetX < minX) {
        world->x += player->x;
    }
    if(player->y + offsetY > maxY) {
        world->y += player->y - maxY;
    } else if(player->y + offsetY < minY) {
        world->y += player->y;
    }

    // Check for collision with world boundaries
    for (Obstacle& obstacle : world->obstacles) {
        if (checkCollision(player, &obstacle)) {
            std::cout << "Collision detected with obstacle at (" << obstacle.x << ", " << obstacle.y << ")" << std::endl;

            // Handle collision (e.g., stop movement or adjust position)
            if (player->vx > 0) player->x = obstacle.x - player->width; // Collision from the left
            if (player->vx < 0) player->x = obstacle.x + obstacle.width; // Collision from the right
            if (player->vy > 0) player->y = obstacle.y - player->height; // Collision from above
            if (player->vy < 0) player->y = obstacle.y + obstacle.height; // Collision from below

            player->vx = 0; // Stop horizontal movement
            player->vy = 0; // Stop vertical movement
        }
    }

}

void destroyPhysics(Player* player) {
    delete player;
}