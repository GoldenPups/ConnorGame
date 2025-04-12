#ifndef PHYSCIS_H
#define PHYSCIS_H

// Function declarations
#include <time.h>

struct Player {
    float x;
    float y;
    float vx;
    float vy;
};

Player* createPlayer(float x, float y, float vx, float vy);
void updatePhysics(Player* player, float dt);
void destroyPhysics(Player* player);


#endif