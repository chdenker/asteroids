#include "../Vars.h"

#include "Rocket.h"

#include <cmath>

namespace game {

Rocket::Rocket(math::Vec2 position, double angle)
: pos{position},
  angle{angle},
  speed{consts::ROCKET_SPEED},
  exploded{false}
{}

Hitbox Rocket::get_hitbox() const
{
    return Hitbox{pos, consts::ROCKET_SIZE / 2.0f};
}

void Rocket::update()
{
	pos.x = pos.x - speed * std::sin(angle);
    pos.y = pos.y + speed * std::cos(angle);

    if (pos.x < 0 || pos.x > consts::SCR_WIDTH) exploded = true;
    if (pos.y < 0 || pos.y > consts::SCR_HEIGHT) exploded = true;
}

} // namespace game