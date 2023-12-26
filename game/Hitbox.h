#ifndef HITBOX_H
#define HITBOX_H

#include "../Utils.h"

namespace game {

// Despite being called hitboxes, they are actually just circles.
struct Hitbox {
    math::Vec2 pos;
    float radius;
};

}   // namespace game

#endif