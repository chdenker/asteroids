#ifndef HITBOX_H
#define HITBOX_H

#include "../Utils.h"

namespace game {

struct Hitbox {
    math::Vec2 pos;
    uint width;
    uint height;
};

}   // namespace game

#endif