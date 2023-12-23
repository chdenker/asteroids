#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace consts {

auto constexpr GAME_TITLE = "Asteroids";

auto constexpr SCR_WIDTH = 1024;
auto constexpr SCR_HEIGHT = 768;

auto constexpr PLAYER_SIZE = 90;
auto constexpr PLAYER_ACCELERATION = 3;
auto constexpr PLAYER_ROT_SPEED = 0.1;

auto constexpr MAX_ASTEROIDS = 30;
auto constexpr ASTEROID_SIZE_LARGE = 200;
auto constexpr ASTEROID_SIZE_MEDIUM = 100;
auto constexpr ASTEROID_SIZE_SMALL = 50;
auto constexpr ASTEROID_INITIAL_SPEED = 50;
auto constexpr ASTEROID_SCORE = 50;

auto constexpr ROCKET_SPEED = 7;
auto constexpr ROCKETS_MAX = 10;
auto constexpr ROCKET_SIZE = 10; // height of rocket; width is ROCKET_SIZE / 2

auto constexpr FONT_PATH = "Roboto-Bold.ttf";

} // namespace consts

#endif