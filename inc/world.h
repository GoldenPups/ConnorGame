#ifndef WORLD_H
#define WORLD_H

#include <vector>


struct Object { 
    int x;      
    int y;      
    int width;  
    int height; 
    // include rendering info
    
    void (*eventFunc)(); // function pointer for event handling
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



World* createWorld1(const int world_OriginX, const int world_OriginY);
void destroyWorld(World* world);


#endif