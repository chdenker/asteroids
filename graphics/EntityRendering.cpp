#include "EntityRendering.h"

#include "../Constants.h"

#include <array>
#include <cmath>
#include <utility>

#include <iostream>

namespace graphics {

std::pair<float, float> compute_centroid(std::array<Point, 4> vertices)
{
    float sum_x {0.0f};
    float sum_y {0.0f};
    for (Point& p : vertices) {
        sum_x += p.x;
        sum_y += p.y;
    }
    float centroid_x {sum_x / 4};
    float centroid_y {sum_y / 4};
    return { centroid_x, centroid_y };
}

void render_player(Screen& scr, game::Player& p)
{
    std::array<Point, 4> vertices {
        Point{ 0.5f, 1.0f }, // top
        Point{ 0.0f, 0.0f }, // bottom left
        Point{ 0.5f, 0.2f }, // mid
        Point{ 1.0f, 0.0f }  // bottom right
    };

    double rot_cos = std::cos(p.get_angle());
    double rot_sin = std::sin(p.get_angle());

    // Apply rotation to the triangle vertices
    for (Point& v : vertices) {
        float x = v.x;
        float y = v.y;
        v.x = rot_cos * x - rot_sin * y;
        v.y = rot_sin * x + rot_cos * y;
    }

    int scale = 90;
    for (Point& v : vertices) {
        v.x *= scale;
        v.y *= scale;
    }

    // Translate the triangle vertices such that
    // (p.pos.x, p.pos.y) is the centroid of the triangle
    auto [centroid_x, centroid_y] = compute_centroid(vertices);
    double dx = p.pos.x - centroid_x;
    double dy = p.pos.y - centroid_y;
    for (Point& v : vertices) {
        v.x += dx;
        v.y += dy;
    }

    Color col{255, 255, 255};
    scr.render_line(vertices[0], vertices[3], col); // top -> bottom right
    scr.render_line(vertices[3], vertices[2], col); // bottom right -> mid
    scr.render_line(vertices[2], vertices[1], col); // mid -> bottom left
    scr.render_line(vertices[1], vertices[0], col); // bottom left -> top

    scr.render_rectangle(p.pos.x, p.pos.y, 5, 5, { 255, 255, 0 });  // draw pos
}

void render_asteroid(Screen& scr, game::Asteroid& ast)
{
    scr.render_rectangle(ast.x, ast.y, 100, 100, { 255, 0, 0 });
}

} // namespace graphics