#include "physics.h"

Player* createPlayer(float x, float y, float vx, float vy) {
    Player* player = new Player;
    player->x = x;
    player->y = y;
    player->vx = vx;
    player->vy = vy;
    return player;
}

void updatePhysics(Player* player, float dt) {
    player->x += player->vx * dt;
    player->y += player->vy * dt;
}

void destroyPhysics(Player* player) {
    delete player;
}