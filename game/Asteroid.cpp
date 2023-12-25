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
    uint width = sz * cosf(M_PI / 4);
    uint height = sz * sinf(M_PI / 4);
    return Hitbox{math::Vec2{pos.x - width / 2, pos.y - height / 2}, width, height};
}
    
void Asteroid::explode()
{
    switch (size) {
    case Size::LARGE: size = Size::MEDIUM; break;
    case Size::MEDIUM: size = Size::SMALL; break;
    case Size::SMALL: size = Size::DESTROYED; break;
    case Size::DESTROYED: return;
    }
}

} // namespace game