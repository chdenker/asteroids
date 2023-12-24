#include "Screen.h"
#include "GModule.h"

namespace graphics {

Screen::Screen(unsigned int width, unsigned int height, std::unique_ptr<GModule>&& gmod)
: width{width}, height{height}, gmod{std::move(gmod)}
{}

void Screen::clear(Color col)
{
    gmod->clear(col.red, col.green, col.blue);
}

void Screen::render_text(int x, int y, Color col, std::string text)
{
    gmod->render_text(x, y, col.red, col.green, col.blue, text.c_str());
}

void Screen::render_line(math::Vec2 p1, math::Vec2 p2, Color col)
{
    gmod->render_line(p1.x, p1.y, p2.x, p2.y, col.red, col.green, col.blue);
}

void Screen::render_rectangle(int x, int y, int width, int height, Color col)
{
    gmod->render_rectangle(x, y, width, height, col.red, col.green, col.blue);
}

void Screen::render_unfilled_rectangle(int x, int y, int width, int height, Color col)
{
    gmod->render_unfilled_rectangle(x, y, width, height, col.red, col.green, col.blue);
}

void Screen::render_circle(int x, int y, int radius, Color col)
{
    gmod->render_circle(x, y, radius, col.red, col.green, col.blue);
}

void Screen::draw()
{
    gmod->draw();
}

} // namespace graphics