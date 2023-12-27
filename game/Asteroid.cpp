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
    case Size::LARGE:       sz = consts::ASTEROID_SIZE_LARGE; break;
    case Size::MEDIUM:      sz = consts::ASTEROID_SIZE_MEDIUM; break;
    case Size::SMALL:       sz = consts::ASTEROID_SIZE_SMALL; break;
    default:                sz = 0; break;
    }
    return Hitbox{math::Vec2{pos.x, pos.y}, sz / 2.0f};
}
    
void Asteroid::explode()
{
    switch (size) {
    case Size::LARGE:       size = Size::MEDIUM; break;
    case Size::MEDIUM:      size = Size::SMALL; break;
    case Size::SMALL:       size = Size::DESTROYED; break;
    case Size::DESTROYED:   return;
    }
}

uint Asteroid::get_quant_size() const
{
    switch (size) {
    case Size::LARGE:       return consts::ASTEROID_SIZE_LARGE;
    case Size::MEDIUM:      return consts::ASTEROID_SIZE_MEDIUM;
    case Size::SMALL:       return consts::ASTEROID_SIZE_SMALL;
    case Size::DESTROYED:   return 0;
    }
    return 0;
}

void Asteroid::update()
{
    pos.x = pos.x - speed * std::sin(angle);
    while (pos.x - get_quant_size() > consts::SCR_WIDTH)    pos.x = -consts::PLAYER_SIZE;
    while (pos.x + get_quant_size() < 0)                    pos.x = consts::SCR_WIDTH + consts::PLAYER_SIZE;

    pos.y = pos.y + speed * std::cos(angle);
    while (pos.y - get_quant_size() > consts::SCR_HEIGHT)   pos.y = -consts::PLAYER_SIZE;
    while (pos.y + get_quant_size() < 0)                    pos.y = consts::SCR_HEIGHT + consts::PLAYER_SIZE;
}

} // namespace game