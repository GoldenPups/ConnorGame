#include "world.h"
#include "objects.h"

Interact_Object createToilet(int x, int y){
    Interact_Object toilet;
    toilet.objectName = "Toilet";
    toilet.objectTexture = "/objects/toilet_texture.png";
    toilet.x = x;
    toilet.y = y;
    toilet.width = TOILET_WIDTH;
    toilet.height = TOILET_HEIGHT;
    toilet.timesUsed = 0;
    toilet.eventFunc = []() {
        //testing
        // std::cout << "Standing in toilet" << std::endl;
    };
    return toilet;
}