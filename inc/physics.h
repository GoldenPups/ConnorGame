#ifndef PHYSCIS_H
#define PHYSCIS_H

#include "world1.h"
#include <time.h>

struct Player {
    int x;
    int y;
    float vx;
    float vy;
    int width;
    int height;
};

Player* createPlayer(int x, int y, float vx, float vy, int width, int height);
void updatePhysics(Player* player, World* world, float dt);
void checkEvents(Player* player, World* world);
void destroyPhysics(Player* player);


#endif