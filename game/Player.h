#ifndef PLAYER_H
#define PLAYER_H

#include "../Utils.h"

#include "Hitbox.h"
#include "Rocket.h"

#include <array>
#include <chrono>
#include <vector>

namespace game {

class Player {
public:
    using RenderingOutput = std::array<math::Vec2, 4>;
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
    using Duration = std::chrono::milliseconds;

    Player(math::Vec2 position, double angle);
    ~Player() = default;

    void shoot();

    math::Vec2 get_top_position() const;
    math::Vec2 get_mid_position() const;

    Hitbox get_hitbox() const;
    bool has_collided_with(Hitbox h);

    void incr_speed();
    void decr_speed();

    void incr_angle(double val);
    void decr_angle(double val);

    void activate_ghostmode();
    inline bool is_ghost() { return ghost; }
    // Assumes that ghostmode is active!
    Duration get_ghostmode_duration();
    void deactivate_ghostmode();

    void update();

    math::Vec2 pos;
    int speed;
    double angle;
    uint score;
    uint lives;
    std::vector<Rocket> rockets;

    RenderingOutput vertices;

private:
    bool ghost;
    TimePoint ghost_start;
};

} // namespace game

#endif