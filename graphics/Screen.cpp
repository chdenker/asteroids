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

void Screen::render_rectangle(int x, int y, int width, int height, Color col)
{
    gmod->render_rectangle(x, y, width, height, col.red, col.green, col.blue);
}

void Screen::render_triangle()
{
    gmod->render_triangle();
}

void Screen::draw()
{
    gmod->draw();
}

} // namespace graphics