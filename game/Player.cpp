#include "Player.h"

#include "../Constants.h"

#include <algorithm>
#include <cmath>
#include <utility>

namespace game {

Player::Player(math::Vec2 position, double angle)
: pos{position},
  dir{0.0f, 1.0f},
  speed{0},
  score{0},
  lives{3},
  rockets{},
  angle{angle}
{
    rockets.reserve(consts::ROCKETS_MAX);
}

math::Vec2 Player::get_top_position() const
{
    return vertices[0];    
}

void Player::incr_angle(double val)
{
    angle = angle + val;
    while (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
}

void Player::decr_angle(double val)
{
    angle = angle - val;
    while (angle < 0) {
        angle += 2 * M_PI;
    }
}

Hitbox Player::get_hitbox() const
{
    auto const [min_x_vertex_it, max_x_vertex_it] = std::minmax_element(vertices.begin(), vertices.end(), [](auto a, auto b){ return a.x < b.x; });
    auto const [min_y_vertex_it, max_y_vertex_it] = std::minmax_element(vertices.begin(), vertices.end(), [](auto a, auto b){ return a.y < b.y; });
    math::Vec2 const& min_x_vertex = *min_x_vertex_it;
    math::Vec2 const& min_y_vertex = *min_y_vertex_it;
    math::Vec2 const& max_x_vertex = *max_x_vertex_it;
    math::Vec2 const& max_y_vertex = *max_y_vertex_it;
    math::Vec2 top_left{min_x_vertex.x, min_y_vertex.y};
    math::Vec2 bottom_right{max_x_vertex.x, max_y_vertex.y};
    uint width = bottom_right.x - top_left.x;
    uint height = bottom_right.y - top_left.y;
    return Hitbox{top_left, width, height};
}

void Player::shoot()
{
    if (rockets.size() < consts::ROCKETS_MAX) {
        rockets.emplace_back(Rocket{get_top_position(), angle});
    }
}

void Player::update()
{
    // Get current direction vector (dir_x,dir_y) first...
    float dir_x = dir.x;
    float dir_y = dir.y;
    // ... then rotate by the current angle
    double rot_cos = std::cos(angle);
    double rot_sin = std::sin(angle);
    float trans_x = rot_cos * dir_x - rot_sin * dir_y;
    float trans_y = rot_sin * dir_x + rot_cos * dir_y;

    // Apply translation
    pos.x = pos.x + consts::PLAYER_ACCELERATION * trans_x;
    while (pos.x - consts::PLAYER_SIZE > consts::SCR_WIDTH) pos.x = -consts::PLAYER_SIZE;
    while (pos.x + consts::PLAYER_SIZE < 0) pos.x = consts::SCR_WIDTH + consts::PLAYER_SIZE;
    pos.y = pos.y + consts::PLAYER_ACCELERATION * trans_y;
    while (pos.y - consts::PLAYER_SIZE > consts::SCR_HEIGHT) pos.y = -consts::PLAYER_SIZE;
    while (pos.y + consts::PLAYER_SIZE < 0) pos.y = consts::SCR_HEIGHT + consts::PLAYER_SIZE;

    for (auto it = rockets.begin(); it != rockets.end(); ) {
        Rocket& r = *it;    
        r.update();
        if (r.exploded) {
            it = rockets.erase(it);
        } else {
            ++it;
        }    
    }
}

} // namespace game
