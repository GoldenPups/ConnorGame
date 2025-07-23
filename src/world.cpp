#include "world.h"
#include "physics.h"
#include "save.h"
#include "map_exporter.h"
#include "objects.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void event1() {
    std::cout << "Event 1 triggered!" << std::endl;
}

vector<Object> createObstaclesFromBinary(string world_0b) {
    vector<Object> obstacles;

    // Parse the string into a 2D grid
    vector<vector<char>> grid;
    vector<char> row;
    for (char c : world_0b) {
        if (c == '\n') {
            if (!row.empty()) grid.push_back(row);
            row.clear();
        } else {
            row.push_back(c);
        }
    }
    if (!row.empty()) grid.push_back(row);

    int rows = grid.size();
    int cols = rows > 0 ? grid[0].size() : 0;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int numObstacles = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '1' && !visited[r][c]) {
                // Find width
                int width = 0;
                while (c + width < cols && grid[r][c + width] == '1' && !visited[r][c + width]) {
                    ++width;
                }
                // Find height
                int height = 0;
                bool done = false;
                while (r + height < rows && !done) {
                    for (int x = 0; x < width; ++x) {
                        if (grid[r + height][c + x] != '1' || visited[r + height][c + x]) {
                            done = true;
                            break;
                        }
                    }
                    if (!done) ++height;
                }
                // Mark visited
                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        visited[r + y][c + x] = true;
                    }
                }
                // Add obstacle (convert to world coordinates)
                numObstacles++;
                obstacles.push_back({
                    c * WORLD_TILE_SIZE,
                    r * WORLD_TILE_SIZE,
                    width * WORLD_TILE_SIZE,
                    height * WORLD_TILE_SIZE
                });
            }
        }
    }
    cout << "Number of obstacles: " << numObstacles << endl;
    cout << "Dimensions of world: " << rows << " : " << cols << endl;
    exportMapAsPNG(grid); // Saves grid as PNG for visualization
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

    world->collisionBoxes.push_back({-100,-100,world_Width + 200,100}); //world top
    world->collisionBoxes.push_back({-100,0,100,world_Height}); // world left
    world->collisionBoxes.push_back({-100,world_Height,world_Width + 200,100}); // world bottom
    world->collisionBoxes.push_back({world_Width,0,100,world_Height}); // world right
    world->collisionBoxes.push_back({200, 200, 50, 50}); // Add an obstacle at (200, 200) with size 50x50
    world->collisionBoxes.push_back({400, 300, 100, 100}); // Add another obstacle

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

    world->collisionBoxes = createObstaclesFromBinary(read_binary_file_as_string("assets/worlds/world1.bin"));
    world->objects.push_back(createToilet(200, 200));

    return world;
}

void destroyWorld(World* world) {
    delete world;
}