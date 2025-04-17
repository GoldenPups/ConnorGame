#include "world1.h"

World* createWorld() {
    World* world = new World;
    world->x = world_OriginX;
    world->y = world_OriginY;
    world->width = world_Width;
    world->height = world_Height;
    return world;
}

void destroyWorld(World* world) {
    delete world;
}