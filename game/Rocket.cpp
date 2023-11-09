#include "../Constants.h"

#include "Rocket.h"

#include <cmath>

namespace game {

Rocket::Rocket(math::Vec2 position, double angle)
: pos{position},
  angle{angle},
  speed{consts::ROCKET_SPEED},
  exploded{false}
{}

void Rocket::update()
{
    // Move forward in current direction
    float dir_x = 0.0f;
    float dir_y = 1.0f;
    double rot_cos = std::cos(angle);
    double rot_sin = std::sin(angle);
	float trans_x = rot_cos * dir_x - rot_sin * dir_y;
	float trans_y = rot_sin * dir_x + rot_cos * dir_y;

	pos.x = pos.x + speed * trans_x;
    pos.y = pos.y + speed * trans_y;

    if (pos.x < 0 || pos.x > consts::SCR_WIDTH) exploded = true;
    if (pos.y < 0 || pos.y > consts::SCR_HEIGHT) exploded = true;
}

} // namespace game