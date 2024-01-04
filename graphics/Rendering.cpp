#include "Rendering.h"

#include "../Vars.h"

#include <array>
#include <cmath>
#include <string>
#include <utility>

namespace graphics {

void render_text(Screen& scr, math::Vec2 pos, Color col, std::string text)
{
    scr.render_text(pos.x, pos.y, col, text);
}

void render_hud(Screen& scr, game::Player& player)
{
    render_text(scr, math::Vec2{0, 0}, { 255, 255, 255 }, std::to_string(player.score));
    render_text(scr, math::Vec2{0, consts::FONT_SIZE}, { 255, 255, 255 }, std::to_string(player.lives));
}

void render_hitbox(Screen& scr, game::Hitbox h, Color col)
{
    scr.render_circle(h.pos.x, h.pos.y, h.radius, col);
}

void render_rockets(Screen& scr, std::vector<game::Rocket>& rockets)
{
    for (game::Rocket const& r : rockets) {
        scr.render_rectangle(r.pos.x, r.pos.y, consts::ROCKET_SIZE / 2, consts::ROCKET_SIZE, { 255, 255, 255 });
    }
}

void render_player(Screen& scr, game::Player& p)
{
    std::array<math::Vec2, 4> vertices {
        math::Vec2{ 0.5f, 1.0f }, // top
        math::Vec2{ 0.0f, 0.0f }, // bottom left
        math::Vec2{ 0.5f, 0.2f }, // mid
        math::Vec2{ 1.0f, 0.0f }  // bottom right
    };

    for (auto& v : vertices) {
        v.rotate(p.angle);
        v.x *= consts::PLAYER_SIZE;
        v.y *= consts::PLAYER_SIZE;
    }

    // Translate the triangle vertices such that p.pos is equivalent to the top vertex
    auto& top = vertices[0];
    float dx = p.pos.x - top.x;
    float dy = p.pos.y - top.y;
    for (auto& v : vertices) {
        v.x += dx;
        v.y += dy;
    }

    Color col;
    if (p.is_ghost()) {
        col = Color{0, 0, 255};
    } else {
        col = Color{255, 255, 255};
    }
    scr.render_line(vertices[0], vertices[3], col); // top -> bottom right
    scr.render_line(vertices[3], vertices[2], col); // bottom right -> mid
    scr.render_line(vertices[2], vertices[1], col); // mid -> bottom left
    scr.render_line(vertices[1], vertices[0], col); // bottom left -> top

    scr.render_rectangle(p.pos.x, p.pos.y, 5, 5, { 255, 255, 0 });  // draw pos

    render_rockets(scr, p.rockets);

    p.vertices = vertices;
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
}

} // namespace graphics