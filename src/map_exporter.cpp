#include "lodepng.h"
#include <vector>
#include <string>

void exportMapAsPNG(const std::vector<std::vector<char>>& grid) {
    const unsigned scale = 50;
    unsigned height = grid.size();
    unsigned width = height ? grid[0].size() : 0;
    unsigned out_height = height * scale;
    unsigned out_width = width * scale;
    std::vector<unsigned char> image(out_width * out_height * 4);

    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            unsigned char r, g, b, a;
            if (grid[y][x] == '1') {
                r = g = b = 0; a = 255; // black
            } else {
                r = g = b = 255; a = 255; // white
            }
            // Fill the 50x50 block
            for (unsigned dy = 0; dy < scale; ++dy) {
                for (unsigned dx = 0; dx < scale; ++dx) {
                    unsigned out_x = x * scale + dx;
                    unsigned out_y = y * scale + dy;
                    unsigned idx = 4 * (out_y * out_width + out_x);
                    image[idx + 0] = r;
                    image[idx + 1] = g;
                    image[idx + 2] = b;
                    image[idx + 3] = a;
                }
            }
        }
    }

    unsigned error = lodepng::encode("assets/worlds/map.png", image, out_width, out_height);
    if (error) {
        printf("PNG encode error %u: %s\n", error, lodepng_error_text(error));
    }
}