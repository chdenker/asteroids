#ifndef PLAYER_H
#define PLAYER_H

#include "../Constants.h"
#include "../Utils.h"

#include "Hitbox.h"

namespace game {

struct Rocket {
    uint x;
    uint y;
    double angle;
    uint speed;
};

class Player {
public:
    Player(math::Vec2 position, double angle);
    ~Player() = default;

    Rocket shoot();

    Hitbox get_hitbox();
    bool has_collided_with(Hitbox h);

    inline double get_angle() { return angle; }
    void incr_angle(double val);
    void decr_angle(double val);

    math::Vec2 pos;
    math::Vec2 dir;
    int speed;
    uint score;
    uint lives;
    
private:
    double angle;
};

} // namespace game

#endif