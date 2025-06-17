#ifndef PHYSCIS_H
#define PHYSCIS_H

#define playerWidth 30
#define playerHeight 30

#include "world.h"
#include <time.h>

struct Player {
    float x;
    float y;
    float vx;
    float vy;
    int width;
    int height;
};

Player* createPlayer(float x, float y, float vx, float vy, int width, int height);
void updatePhysics(Player* player, World* world, float deltaTime, bool wallHacks);
void checkEvents(Player* player, World* world);
void destroyPhysics(Player* player);

#endif