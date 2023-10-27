#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

using uint = std::uint32_t;

namespace consts {

auto constexpr GAME_TITLE = "Asteroids";

auto constexpr SCR_WIDTH = 1024;
auto constexpr SCR_HEIGHT = 768;

auto constexpr PLAYER_WIDTH = 20;
auto constexpr PLAYER_HEIGHT = 30;

auto constexpr MAX_ASTEROIDS = 30;

auto constexpr MAX_PLAYER_SPEED = 50;
auto constexpr PLAYER_ACCELERATION = 7;
auto constexpr PLAYER_ROT_SPEED = 0.1;

auto constexpr ASTEROID_INITIAL_SPEED = 50;

auto constexpr ROCKET_SPEED = 100;

} // namespace consts

#endif