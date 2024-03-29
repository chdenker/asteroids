#ifndef ROCKET_H
#define ROCKET_H

#include "../Utils.h"

#include "Hitbox.h"

namespace game {

class Rocket {
public:
    Rocket(math::Vec2 position, double angle);
    ~Rocket() = default;

    Hitbox get_hitbox() const;

    void update();

    math::Vec2 pos;
    double angle;
    uint speed;
    bool exploded;
};

} // namespace game

#endif