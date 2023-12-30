#ifndef ASTEROID_H
#define ASTEROID_H

#include "../Vars.h"
#include "../Utils.h"

#include "Hitbox.h"

namespace game {

class Asteroid {
public:
    enum class Size {
        LARGE, MEDIUM, SMALL, DESTROYED
    };

    Asteroid(math::Vec2 pos, uint angle, Size size = Size::LARGE, uint speed = consts::ASTEROID_INITIAL_SPEED);
    Asteroid(Asteroid const& a) = default;

    ~Asteroid() = default;

    Hitbox get_hitbox() const;
    int get_quant_size() const;

    void update();
    void explode();

    math::Vec2 pos;
    uint angle;
    uint speed;
    Size size;
};

} // namespace game

#endif