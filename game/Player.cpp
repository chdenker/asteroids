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
  rockets{},
  angle{angle}
{
    rockets.reserve(consts::ROCKETS_MAX);
}

math::Vec2 Player::get_top_position()
{
    // Get current direction vector (with length consts::PLAYER_SIZE)
    math::Vec2 v = dir;
    double rot_cos = std::cos(get_angle());
    double rot_sin = std::sin(get_angle());
    float x = v.x;
    float y = v.y;
    v.x = rot_cos * x - rot_sin * y;
    v.y = rot_sin * x + rot_cos * y;
    // ... Normalize to length consts::PLAYER_SIZE
    float scale = consts::PLAYER_SIZE / std::hypot(v.x, v.y);
    v.x *= scale;
    v.y *= scale;
    // Add direction vector to current position
    return {pos.x + v.x, pos.y + v.y};
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

Hitbox Player::get_hitbox()
{
    return {};
    // return std::move(Hitbox{x, y, consts::PLAYER_WIDTH, consts::PLAYER_HEIGHT});
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