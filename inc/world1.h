#ifndef WORLD1_H
#define WORLD1_H

#include <vector>

#define world_Width 1000
#define world_Height 1000
#define world_OriginX 100
#define world_OriginY 100

struct Obstacle {
    int x;      // X position of the obstacle
    int y;      // Y position of the obstacle
    int width;  // Width of the obstacle
    int height; // Height of the obstacle
};

// World position
struct World {
    int x;
    int y;
    int width;
    int height;
    std::vector<Obstacle> obstacles; // List of obstacles
};



World* createWorld();
void destroyWorld(World* world);


#endif