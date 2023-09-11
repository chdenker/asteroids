#ifndef SCREEN_H
#define SCREEN_H

#include "GModule.h"

#include <memory>

namespace graphics {

struct Color {
    int red;
    int green;
    int blue;
};

class Screen {
public:
    Screen(unsigned int width, unsigned int height, std::unique_ptr<GModule>&& gmod);
    ~Screen() = default;

    void clear(Color col);
    void render_rectangle(int x, int y, int width, int height, Color col);
    void render_triangle();
    void draw();

private:
    unsigned int width;
    unsigned int height;
    std::unique_ptr<GModule> gmod;
};

} // namespace graphics

#endif