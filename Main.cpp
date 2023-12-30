#include "Constants.h"

#include "game/Hitbox.h"
#include "game/Player.h"
#include "game/Asteroid.h"

#include "graphics/Screen.h"
#include "graphics/GModule.h"
#include "graphics/Rendering.h"

#include <SDL2/SDL.h>

#include <array>
#include <iostream>
#include <memory>
#include <vector>

bool game_running = false;
bool hitbox_rendering = false;

enum class GameState {
    MENU, INGAME, GAMEOVER
} state{GameState::MENU};

auto constexpr MAX_LEVEL = 6;
std::array<uint, MAX_LEVEL> asteroid_amounts{
   1, 2, 2, 3, 3, 3
};
uint curr_lvl = 0;

struct Input {
    bool left;
    bool right;
    bool up;
    bool down;
    bool space, space_held;
    bool r;
};

// TODO: Hide the SDL dependency
void process_input(Input& in)
{
    SDL_Event e;
    SDL_PollEvent(&e);
    switch (e.type) {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            in.left = true;
            break;
        case SDLK_RIGHT:
            in.right = true;
            break;
        case SDLK_UP:
            in.up = true;
            break;
        case SDLK_DOWN:
            in.down = true;
            break;
        case SDLK_SPACE:
            in.space = true;
            break;
        case SDLK_r:
            in.r = true;
            break;
        case SDLK_h:
            hitbox_rendering = !hitbox_rendering;
            std::cout << "hitbox_rendering = " << hitbox_rendering << std::endl;
            break;
        case SDLK_ESCAPE:
            game_running = false;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (e.key.keysym.sym) {
        case SDLK_LEFT:
            in.left = false;
            break;
        case SDLK_RIGHT:
            in.right = false;
            break;
        case SDLK_UP:
            in.up = false;
            break;
        case SDLK_DOWN:
            in.down = false;
            break;
        case SDLK_SPACE:
            in.space = false;
            in.space_held = false;
            break;
        case SDLK_r:
            in.r = false;
            break;
        }
        break;    
    case SDL_QUIT:
        game_running = false;
        break;
    }
}

bool collides_with(game::Hitbox const& a, game::Hitbox const& b)
{
    float dist = std::hypot(a.pos.x - b.pos.x, a.pos.y - b.pos.y);
    return dist < a.radius + b.radius;
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
        if (collides_with(player_hbox, ast_hbox)) {
            --player.lives;
            if (player.lives == 0) {
                state = GameState::GAMEOVER;
                break;
            }
            player.pos = math::Vec2{700.0f, 300.0f};
            player.speed = 0;
            player.angle = 0;
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

void generate_level(std::vector<game::Asteroid>& asteroids, uint current_level)
{
    uint ast_amount = asteroid_amounts[current_level];
    for (uint i = 0; i < ast_amount; ++i) {
        asteroids.emplace_back(math::Vec2{200.0f + i * 250.0f, 400.0f}, 0, game::Asteroid::Size::LARGE, 1);
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
        generate_level(asteroids, curr_lvl);
    }
}

bool handle_game_over(graphics::Screen& scr, Input& in)
{
    if (in.r) {
        return true; // restart requested
    }

    graphics::render_text(scr, math::Vec2{consts::SCR_WIDTH / 2, consts::SCR_HEIGHT / 2}, { 255, 255, 255 }, "GAME OVER");
    return false;   // no restart
}

int main()
{
    std::unique_ptr<GModule> gmod = std::make_unique<GModule>(consts::SCR_WIDTH, consts::SCR_HEIGHT);
    graphics::Screen scr{consts::SCR_WIDTH, consts::SCR_HEIGHT, std::move(gmod)};
    Input in{};

    game::Player player{math::Vec2{700.0f, 300.0f}, 0};
    std::vector<game::Asteroid> asteroids{};
    asteroids.reserve(consts::MAX_ASTEROIDS);

    generate_level(asteroids, curr_lvl);

    state = GameState::INGAME;

    game_running = true;
    while (game_running) {
        process_input(in);

        if (state == GameState::INGAME) {
            scr.clear({0, 0, 0});
            update(in, player, asteroids);

            graphics::render_hud(scr, player);

            graphics::render_player(scr, player);
            for (auto& a : asteroids) graphics::render_asteroid(scr, a);

            if (hitbox_rendering) {
                graphics::render_hitbox(scr, player.get_hitbox(), { 0, 0, 255 });
                for (auto& r : player.rockets) render_hitbox(scr, r.get_hitbox(), { 255, 165, 0 });
                for (auto& a : asteroids) render_hitbox(scr, a.get_hitbox(), { 255, 0, 0 });
            }

        } else if (state == GameState::GAMEOVER) {
            bool restart_requested = handle_game_over(scr, in);
            if (restart_requested) {
                player = game::Player{math::Vec2{700, 300}, 0};
                asteroids.clear();
                curr_lvl = 0;
                generate_level(asteroids, curr_lvl);

                state = GameState::INGAME;
            }
        }

        scr.draw();

        // SDL_Delay(60);	// TODO: Add timing logic
    }

    return 0;
}
