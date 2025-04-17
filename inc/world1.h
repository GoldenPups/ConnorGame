#ifndef WORLD1_H
#define WORLD1_H

#define world_Width 1000
#define world_Height 1000
#define world_OriginX 100
#define world_OriginY 100

// World position
struct World {
    int x;
    int y;
    int width;
    int height;
};


World* createWorld();
void destroyWorld(World* world);


#endif