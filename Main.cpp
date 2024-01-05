#include "Input.h"
#include "Vars.h"

#include "game/Hitbox.h"
#include "game/Player.h"
#include "game/Asteroid.h"

#include "graphics/Screen.h"
#include "graphics/GModule.h"
#include "graphics/Rendering.h"

#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

namespace global {
    bool game_running = false;
    bool hitbox_rendering = false;

    GameState state = GameState::MENU;
} // namespace global

auto constexpr MAX_LEVEL = 6;
std::array<uint, MAX_LEVEL> asteroid_amounts{
   1, 2, 2, 3, 3, 3
};
uint curr_lvl = 0;

bool collides_with(game::Hitbox const& a, game::Hitbox const& b)
{
    float dist = std::hypot(a.pos.x - b.pos.x, a.pos.y - b.pos.y);
    return dist <= a.radius + b.radius;
}

void handle_input(Input& in, game::Player& player)
{
    if (in.up) {
        player.incr_speed();
    } else if (in.down) {
        player.decr_speed();
    }

    if (in.left) {
        player.decr_angle(consts::PLAYER_ROT_SPEED);
    } else if (in.right) {
        player.incr_angle(consts::PLAYER_ROT_SPEED);
    }

    if (in.space && !in.space_held) {
        player.shoot();
        in.space_held = true;
    }
}

void handle_collisions(game::Player& player, std::vector<game::Asteroid>& asteroids)
{
    game::Hitbox player_hbox = player.get_hitbox();
    for (game::Asteroid& ast : asteroids) {
        game::Hitbox ast_hbox = ast.get_hitbox();
        if (!player.is_ghost() && collides_with(player_hbox, ast_hbox)) {
            --player.lives;
            if (player.lives == 0) {
                global::state = global::GameState::GAMEOVER;
                break;
            }
            player.pos = math::Vec2{consts::PLAYER_INIT_X, consts::PLAYER_INIT_Y};
            player.speed = 0;
            player.angle = 0;
            player.activate_ghostmode();
        }
        for (game::Rocket& r : player.rockets) {
            game::Hitbox r_hbox = r.get_hitbox();
            if (collides_with(r_hbox, ast_hbox)) {
                player.score += consts::ASTEROID_SCORE;
                r.exploded = true;
                ast.explode();
                ast.speed *= 2;
                asteroids.emplace_back(ast.pos, ast.angle + M_PI / 2, ast.size, ast.speed);
                if (ast.size == game::Asteroid::Size::SMALL) {
                    asteroids.emplace_back(ast.pos, ast.angle + 3 * M_PI / 4, ast.size, ast.speed);
                    asteroids.emplace_back(ast.pos, ast.angle + 5 * M_PI / 4, ast.size, ast.speed);
                }
            }
        }
    }
}

void generate_level(std::vector<game::Asteroid>& asteroids, game::Player& player, uint current_level)
{
    uint ast_amount = asteroid_amounts[current_level];
    for (uint i = 0; i < ast_amount; ++i) {
        float ast_x, ast_y;
        do {
            ast_x = std::rand() % (consts::SCR_WIDTH - consts::ASTEROID_SIZE_LARGE) + consts::ASTEROID_SIZE_LARGE;
            ast_y = std::rand() % (consts::SCR_HEIGHT - consts::ASTEROID_SIZE_LARGE) + consts::ASTEROID_SIZE_LARGE;
        } while (std::hypot(ast_x - player.pos.x, ast_y - player.pos.y) < 2 * consts::PLAYER_SIZE + consts::ASTEROID_SIZE_LARGE);
        asteroids.emplace_back(math::Vec2{ast_x, ast_y}, 0, game::Asteroid::Size::LARGE, consts::ASTEROID_INITIAL_SPEED);
    }
}

void update(Input& in, game::Player& player, std::vector<game::Asteroid>& asteroids)
{
    handle_input(in, player);

    player.update();
    for (game::Asteroid& ast : asteroids) ast.update();

    handle_collisions(player, asteroids);

    for (auto it = asteroids.begin(); it != asteroids.end(); ) {
        game::Asteroid& ast = *it;
        if (ast.size == game::Asteroid::Size::DESTROYED) {
            it = asteroids.erase(it);
        } else {
            ++it;
        }
    }

    if (asteroids.size() == 0) {
        curr_lvl = (curr_lvl + 1) % MAX_LEVEL;
        generate_level(asteroids, player, curr_lvl);
    }
}

bool handle_game_over(graphics::Screen& scr, Input& in)
{
    if (in.r) {
        return true; // restart requested
    }

    float text_x = consts::SCR_WIDTH / 2 - 2.5f * consts::FONT_SIZE;
    float text_y = consts::SCR_HEIGHT / 2;
    graphics::render_text(scr, math::Vec2{text_x, text_y}, { 255, 255, 255 }, "WASTED!");
    return false;   // no restart
}

int main()
{
    std::unique_ptr<GModule> gmod = std::make_unique<GModule>(consts::SCR_WIDTH, consts::SCR_HEIGHT);
    graphics::Screen scr{consts::SCR_WIDTH, consts::SCR_HEIGHT, std::move(gmod)};
    Input in{};

    game::Player player{math::Vec2{consts::PLAYER_INIT_X, consts::PLAYER_INIT_Y}, 0};
    std::vector<game::Asteroid> asteroids{};
    asteroids.reserve(consts::MAX_ASTEROIDS);

    std::srand(std::time(nullptr));
    generate_level(asteroids, player, curr_lvl);

    global::state = global::GameState::INGAME;

    auto next_update = std::chrono::high_resolution_clock::now();
    auto current_time = std::chrono::high_resolution_clock::now();

    global::game_running = true;
    while (global::game_running) {
        current_time = std::chrono::high_resolution_clock::now();

        process_input(in);

        if (global::state == global::GameState::INGAME) {
            scr.clear({0, 0, 0});

            while (next_update < current_time) {
                update(in, player, asteroids);
                next_update += std::chrono::milliseconds{consts::SKIP_TICKS};
            }

            graphics::render_hud(scr, player);

            graphics::render_player(scr, player);
            for (auto& a : asteroids) graphics::render_asteroid(scr, a);

            if (global::hitbox_rendering) {
                graphics::render_hitbox(scr, player.get_hitbox(), { 0, 0, 255 });
                for (auto& r : player.rockets) render_hitbox(scr, r.get_hitbox(), { 255, 165, 0 });
                for (auto& a : asteroids) render_hitbox(scr, a.get_hitbox(), { 255, 0, 0 });
            }

        } else if (global::state == global::GameState::GAMEOVER) {
            bool restart_requested = handle_game_over(scr, in);
            if (restart_requested) {
                player = game::Player{math::Vec2{consts::PLAYER_INIT_X, consts::PLAYER_INIT_Y}, 0};
                asteroids.clear();
                curr_lvl = 0;
                generate_level(asteroids, player, curr_lvl);

                global::state = global::GameState::INGAME;
            }
        }

        scr.draw();

    }

    return 0;
}
