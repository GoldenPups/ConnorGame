#ifndef PHYSCIS_H
#define PHYSCIS_H

#include "world.h"
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
void updatePhysics(Player* player, World* world);
void checkEvents(Player* player, World* world);
void destroyPhysics(Player* player);


#endif