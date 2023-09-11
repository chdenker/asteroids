#ifndef PLAYER_H
#define PLAYER_H

#include "../Constants.h"

#include "Hitbox.h"

namespace game {

struct Rocket {
    uint x;
    uint y;
    uint angle;
    uint speed;
};

class Player {
public:
    Player(uint x, uint y, uint angle);
    ~Player() = default;

    Rocket shoot();

    Hitbox get_hitbox();
    bool has_collided_with(Hitbox h);

    uint x;
    uint y;
    uint angle;
    uint speed;
    uint score;
    uint lives;
};

} // namespace game

#endif