#include "Asteroid.h"

#include <cmath>

namespace game {

Asteroid::Asteroid(math::Vec2 pos, uint angle, Size size, uint speed)
: pos{pos}, angle{angle}, speed{speed}, size{size}
{}

Hitbox Asteroid::get_hitbox() const
{
    uint sz;
    switch (size) {
    case Size::LARGE: sz = consts::ASTEROID_SIZE_LARGE; break;
    case Size::MEDIUM: sz = consts::ASTEROID_SIZE_MEDIUM; break;
    case Size::SMALL: sz = consts::ASTEROID_SIZE_SMALL; break;
    default: sz = 0; break;
    }
    return Hitbox{pos.x - sz / 2, pos.y - sz / 2, sz, sz};
}

} // namespace game