#include "physics.h"
#include "world1.h"
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

void updatePhysics(Player* player, World* world, float dt) {
    player->x += player->vx * dt;
    player->y += player->vy * dt;

    // Check for collision with world boundaries
    int maxX = window_Width - player->width;
    int maxY = window_Height - player->height;
    int minX = 0;
    int minY = 0;

    if(player->x > maxX) {
        world->x += player->x - maxX;
        player->x = maxX;
    } else if(player->x < minX) {
        world->x += player->x;
        player->x = minX;
    }
    if(player->y > maxY) {
        world->y += player->y - maxY;
        player->y = maxY;
    } else if(player->y < minY) {
        world->y += player->y;
        player->y = minY;
    }

}

void destroyPhysics(Player* player) {
    delete player;
}