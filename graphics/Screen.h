#ifndef SCREEN_H
#define SCREEN_H

#include "../Utils.h"
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
    void render_text(int x, int y, Color col, std::string text);
    void render_line(math::Vec2 p1, math::Vec2 p2, Color col);
    void render_rectangle(int x, int y, int width, int height, Color col);
    void render_unfilled_rectangle(int x, int y, int width, int height, Color col);
    void render_circle(int x, int y, int radius, Color col);
    void draw();

private:
    unsigned int width;
    unsigned int height;
    std::unique_ptr<GModule> gmod;
};

} // namespace graphics

#endif