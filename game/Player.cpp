#include "Player.h"

#include "../Constants.h"

#include <cmath>
#include <utility>

namespace game {

Player::Player(math::Vec2 position, double angle)
: pos{position},
  dir{0.0f, 1.0f},
  speed{0},
  score{0},
  lives{3},
  angle{angle}
{}

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

Hitbox Player::get_hitbox()
{
    return {};
    // return std::move(Hitbox{x, y, consts::PLAYER_WIDTH, consts::PLAYER_HEIGHT});
}

Rocket Player::shoot()
{
    return {};
    // return std::move(Rocket{ x, y, angle, consts::ROCKET_SPEED });
}

} // namespace game