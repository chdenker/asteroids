#include "EntityRendering.h"

#include "../Constants.h"

#include <array>
#include <cmath>

namespace graphics {

void render_player(Screen& scr, game::Player& p)
{
    std::array<Point, 3> vertices {
        Point{ 0.5f, 1.0f }, // top
        Point{ 0.0f, 0.0f }, // left
        Point{ 1.0f, 0.0f }  // right
    };

    int scale = 100;
    for (Point& v : vertices) {
        v.x *= scale;
        v.y *= scale;
    }
    double rot_cos = std::cos(p.angle);
    double rot_sin = std::sin(p.angle);

    // Apply rotation and translation to the triangle vertices
    for (Point& v : vertices) {
        float x = v.x;
        float y = v.y;
        v.x = rot_cos * x - rot_sin * y + p.x;
        v.y = rot_sin * x + rot_cos * y + p.y;
    }

    Color col{255, 255, 255};
    scr.render_line(vertices[0], vertices[2], col); // top -> right
    scr.render_line(vertices[2], vertices[1], col); // right -> left
    scr.render_line(vertices[1], vertices[0], col); // left -> top
}

void render_asteroid(Screen& scr, game::Asteroid& ast)
{
    scr.render_rectangle(ast.x, ast.y, 100, 100, { 255, 0, 0 });
}

} // namespace graphics