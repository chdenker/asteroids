#ifndef VARS_H
#define VARS_H

// Global variables
namespace global {

extern bool game_running;
extern bool hitbox_rendering;

extern enum class GameState {
    MENU, INGAME, GAMEOVER
} state;

} // namespace global


// Constants
namespace consts {

auto constexpr GAME_TITLE = "Asteroids";

auto constexpr SCR_WIDTH = 1024;
auto constexpr SCR_HEIGHT = 768;

auto constexpr UPDATES_PER_SEC = 25;
auto constexpr SKIP_TICKS = 1000 / UPDATES_PER_SEC; // time between two ticks

auto constexpr PLAYER_SIZE = 90;
auto constexpr PLAYER_INIT_X = SCR_WIDTH / 2;
auto constexpr PLAYER_INIT_Y = SCR_HEIGHT / 2;
auto constexpr PLAYER_ACCELERATION = 1;
auto constexpr PLAYER_MAX_SPEED = 9;   // should be less than ROCKET_SPEED
auto constexpr PLAYER_ROT_SPEED = 0.2;
auto constexpr PLAYER_LIVES = 3;

auto constexpr MAX_ASTEROIDS = 30;
auto constexpr ASTEROID_SIZE_LARGE = 200;
auto constexpr ASTEROID_SIZE_MEDIUM = 100;
auto constexpr ASTEROID_SIZE_SMALL = 50;
auto constexpr ASTEROID_INITIAL_SPEED = 2;
auto constexpr ASTEROID_SCORE = 50;

auto constexpr ROCKET_SPEED = 16;
auto constexpr ROCKETS_MAX = 5;
auto constexpr ROCKET_SIZE = 10; // height of rocket; width is ROCKET_SIZE / 2

auto constexpr FONT_PATH = "Roboto-Bold.ttf";
auto constexpr FONT_SIZE = 60;

} // namespace consts

#endif