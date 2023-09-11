#include "Player.h"

#include "../Constants.h"

#include <utility>

namespace game {

Player::Player(uint x, uint y, uint angle)
: x{x}, y{y}, angle{angle}, speed{0}, score{0}, lives{3}
{}

Hitbox Player::get_hitbox()
{
    return std::move(Hitbox{x, y, consts::PLAYER_WIDTH, consts::PLAYER_HEIGHT});
}

Rocket Player::shoot()
{
    return std::move(Rocket{ x, y, angle, consts::ROCKET_SPEED });
}

} // namespace game