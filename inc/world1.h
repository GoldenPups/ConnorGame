#ifndef WORLD1_H
#define WORLD1_H

#include <vector>

#define world_Width 1000
#define world_Height 1000
#define world_OriginX 100
#define world_OriginY 100

struct Object { 
    int x;      
    int y;      
    int width;  
    int height; 
};


// World position
struct World {
    int x;
    int y;
    int width;
    int height;
    std::vector<Object> obstacles; // colision checks
    std::vector<Object> objects; // no colision checks (just renderer)
    std::vector<Object> events; // event checks (dialog) 
};



World* createWorld();
void destroyWorld(World* world);


#endif