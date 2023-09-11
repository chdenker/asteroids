#ifndef ASTEROID_H
#define ASTEROID_H

#include "../Constants.h"

#include <cstdint>

namespace game {

class Asteroid {
public:
    enum class Size {
        LARGE, MEDIUM, SMALL, DESTROYED
    };

    Asteroid(uint x, uint y, uint angle, uint speed = consts::ASTEROID_INITIAL_SPEED);
    Asteroid(Asteroid const& a) = default;

    ~Asteroid() = default;

    uint x;
    uint y;
    uint angle;
    uint speed;
    Size size;
};

} // namespace game

#endif