#include "EntityRendering.h"

#include "../Constants.h"

#include <array>
#include <cmath>
#include <utility>

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

void render_hitbox(Screen& scr, game::Hitbox h, Color col)
{
    scr.render_unfilled_rectangle(h.pos.x, h.pos.y, h.width, h.height, col);
}

void render_rockets(Screen& scr, std::vector<game::Rocket>& rockets)
{
    for (game::Rocket const& r : rockets) {
        scr.render_rectangle(r.pos.x, r.pos.y, consts::ROCKET_SIZE / 2, consts::ROCKET_SIZE, { 255, 255, 255 });
        
        render_hitbox(scr, r.get_hitbox(), { 255, 165, 0 });
    }
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

    for (Point& v : vertices) {
        v.x *= consts::PLAYER_SIZE;
        v.y *= consts::PLAYER_SIZE;
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

    render_rockets(scr, p.rockets);

    render_hitbox(scr, p.get_hitbox(), { 0, 0, 255 });
}

void render_asteroid(Screen& scr, game::Asteroid& ast)
{
    int radius = 0;
    switch (ast.size) {
    case game::Asteroid::Size::LARGE: radius = consts::ASTEROID_SIZE_LARGE / 2; break;
    case game::Asteroid::Size::MEDIUM: radius = consts::ASTEROID_SIZE_MEDIUM / 2; break;
    case game::Asteroid::Size::SMALL: radius = consts::ASTEROID_SIZE_SMALL / 2; break;
    case game::Asteroid::Size::DESTROYED: return; // Don't render asteroid
    }
    scr.render_circle(ast.pos.x, ast.pos.y, radius, { 255, 255, 255 });
    render_hitbox(scr, ast.get_hitbox(), { 255, 0, 0 });
}

} // namespace graphics