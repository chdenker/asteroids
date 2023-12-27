#ifndef PLAYER_H
#define PLAYER_H

#include "../Utils.h"

#include "Hitbox.h"
#include "Rocket.h"

#include <array>
#include <vector>

namespace game {

class Player {
public:
    using RenderingOutput = std::array<math::Vec2, 4>;

    Player(math::Vec2 position, double angle);
    ~Player() = default;

    void shoot();

    math::Vec2 get_top_position() const;
    math::Vec2 get_mid_position() const;

    Hitbox get_hitbox() const;
    bool has_collided_with(Hitbox h);

    inline int get_speed() const { return speed; }
    void incr_speed();
    void decr_speed();

    inline double get_angle() const { return angle; }
    void incr_angle(double val);
    void decr_angle(double val);

    void update();

    math::Vec2 pos;
    uint score;
    uint lives;
    std::vector<Rocket> rockets;
    
    RenderingOutput vertices;
    
private:
    int speed;
    double angle;
};

} // namespace game

#endif