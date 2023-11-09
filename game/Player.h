#ifndef PLAYER_H
#define PLAYER_H

#include "../Utils.h"

#include "Hitbox.h"
#include "Rocket.h"

#include <vector>

namespace game {

class Player {
public:
    Player(math::Vec2 position, double angle);
    ~Player() = default;

    void shoot();

    math::Vec2 get_top_position();

    Hitbox get_hitbox();
    bool has_collided_with(Hitbox h);

    inline double get_angle() { return angle; }
    void incr_angle(double val);
    void decr_angle(double val);

    void update();

    math::Vec2 pos;
    math::Vec2 dir;
    int speed;
    uint score;
    uint lives;
    std::vector<Rocket> rockets;
    
private:
    double angle;
};

} // namespace game

#endif