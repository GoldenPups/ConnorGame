#include "world.h"
#include "physics.h"
#include "save.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void event1() {
    std::cout << "Event 1 triggered!" << std::endl;
}

vector<Object> createObstaclesFromBinary(string world_0b) {
    vector<Object> obstacles;
    int y = 0;
    int xOffset = 0;
    for(int i = 0; i < world_0b.length(); i++) {
        if (world_0b[i] == '1') {
            int x = (i) * WORLD_TILE_SIZE - xOffset;
            obstacles.push_back({x, y, WORLD_TILE_SIZE, WORLD_TILE_SIZE});
        } else if (world_0b[i] == '\n') {
            // New line character
            xOffset = (i + 1) * WORLD_TILE_SIZE;
            y += WORLD_TILE_SIZE; // Move to the next row
        } else {
            std::cerr << "Invalid character in world_0b: " << world_0b[i] << std::endl;
        }
    }
    return obstacles;
}

World* createTestGroundWorld(const int world_OriginX, const int world_OriginY) {
    const int world_Width = 1000;
    const int world_Height = 1000;

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

    world->events.push_back({100,100,100,100,event1}); //start

    return world;
}

World* createWorld1(const int world_OriginX, const int world_OriginY) {
    const int world_Width = 1000;
    const int world_Height = 1000;

    World* world = new World;
    world->x = -world_OriginX;
    world->y = -world_OriginY;
    world->width = world_Width;
    world->height = world_Height;

    world->obstacles = createObstaclesFromBinary(read_binary_file_as_string("assets/worlds/world1.bin"));

    return world;
}

void destroyWorld(World* world) {
    delete world;
}