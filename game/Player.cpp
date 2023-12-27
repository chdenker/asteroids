#include "Player.h"

#include "../Constants.h"

#include <cmath>

namespace game {

Player::Player(math::Vec2 position, double angle)
: pos{position},
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

math::Vec2 Player::get_mid_position() const
{
    return vertices[2];
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
    return Hitbox{get_mid_position(), consts::PLAYER_SIZE / 2.5f};
}

void Player::shoot()
{
    if (rockets.size() < consts::ROCKETS_MAX) {
        rockets.emplace_back(Rocket{get_top_position(), angle});
    }
}

void Player::update()
{
    pos.x = pos.x - consts::PLAYER_ACCELERATION * std::sin(angle);
    while (pos.x - consts::PLAYER_SIZE > consts::SCR_WIDTH)     pos.x = -consts::PLAYER_SIZE;
    while (pos.x + consts::PLAYER_SIZE < 0)                     pos.x = consts::SCR_WIDTH + consts::PLAYER_SIZE;

    pos.y = pos.y + consts::PLAYER_ACCELERATION * std::cos(angle);
    while (pos.y - consts::PLAYER_SIZE > consts::SCR_HEIGHT)    pos.y = -consts::PLAYER_SIZE;
    while (pos.y + consts::PLAYER_SIZE < 0)                     pos.y = consts::SCR_HEIGHT + consts::PLAYER_SIZE;

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
