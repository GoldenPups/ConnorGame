#include "world1.h"

World* createWorld() {
    World* world = new World;
    world->x = -world_OriginX;
    world->y = -world_OriginY;
    world->width = world_Width;
    world->height = world_Height;

    world->obstacles.push_back({-100,-100,world_Width + 200,100}); //world top
    world->obstacles.push_back({-100,0,100,world_Height}); // world left
    world->obstacles.push_back({-100,world_Height,world_Width + 200,100}); // world bottom
    world->obstacles.push_back({world_Width,0,100,world_Height}); // world right
    world->obstacles.push_back({200, 200, 50, 50}); // Add an obstacle at (200, 200) with size 50x50
    world->obstacles.push_back({400, 300, 100, 100}); // Add another obstacle

    world->events.push_back({100,100,100,100}); //start

    return world;
}

void destroyWorld(World* world) {
    delete world;
}