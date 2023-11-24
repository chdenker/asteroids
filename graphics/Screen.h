#ifndef SCREEN_H
#define SCREEN_H

#include "GModule.h"

#include <memory>

namespace graphics {

struct Point {
    float x;
    float y;
};

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
    void render_line(Point p1, Point p2, Color col);
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