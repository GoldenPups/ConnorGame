#ifndef PHYSCIS_H
#define PHYSCIS_H

#include "world1.h"
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
void updatePhysics(Player* player, World* world, float dt);
void destroyPhysics(Player* player);


#endif