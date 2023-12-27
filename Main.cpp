#include "Constants.h"

#include "game/Hitbox.h"
#include "game/Player.h"
#include "game/Asteroid.h"

#include "graphics/Screen.h"
#include "graphics/GModule.h"
#include "graphics/Rendering.h"

#include <SDL2/SDL.h>

#include <iostream>
#include <memory>
#include <vector>

bool game_running = false;
bool hitbox_rendering = false;

enum class GameState {
    MENU, INGAME, GAMEOVER
} state{GameState::MENU};

struct Input {
    bool left;
    bool right;
    bool up;
    bool down;
    bool space;
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

void update(Input& in, game::Player& player, std::vector<game::Asteroid>& asteroids)
{
    if (in.up) {
        player.speed = consts::PLAYER_ACCELERATION;
    } else if (in.down) {
        player.speed = -consts::PLAYER_ACCELERATION;
    }

    if (in.left) {
        player.decr_angle(consts::PLAYER_ROT_SPEED);
    } else if (in.right) {
        player.incr_angle(consts::PLAYER_ROT_SPEED);
    }

    if (in.space) {
        player.shoot();
    }

    player.update();

    game::Hitbox player_hbox = player.get_hitbox();
    for (game::Asteroid& ast : asteroids) {
        game::Hitbox ast_hbox = ast.get_hitbox();
        if (collides_with(player_hbox, ast_hbox)) {
            state = GameState::GAMEOVER;
            break;
        }
        for (game::Rocket& r : player.rockets) {
            game::Hitbox r_hbox = r.get_hitbox();
            if (collides_with(r_hbox, ast_hbox)) {
                player.score += consts::ASTEROID_SCORE;
                r.exploded = true;
                ast.explode();
            }
        }
    }

    for (auto it = asteroids.begin(); it != asteroids.end(); ) {
        game::Asteroid& ast = *it;
        if (ast.size == game::Asteroid::Size::DESTROYED) {
            it = asteroids.erase(it);
        } else {
            ++it;
        }
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

    game::Player player{math::Vec2{700, 300}, 0};
    std::vector<game::Asteroid> asteroids{};
    asteroids.reserve(consts::MAX_ASTEROIDS);

    asteroids.emplace_back(math::Vec2{400.0f, 400.0f}, 0, game::Asteroid::Size::LARGE);

    state = GameState::INGAME;

    game_running = true;
    while (game_running) {
        process_input(in);

        if (state == GameState::INGAME) {
            scr.clear({0, 0, 0});

            update(in, player, asteroids);

            graphics::render_player(scr, player);
            for (auto& a : asteroids) graphics::render_asteroid(scr, a);

            if (hitbox_rendering) {
                graphics::render_hitbox(scr, player.get_hitbox(), { 0, 0, 255 });
                for (auto& r : player.rockets) render_hitbox(scr, r.get_hitbox(), { 255, 165, 0 });
                for (auto& a : asteroids) render_hitbox(scr, a.get_hitbox(), { 255, 0, 0 });
            }

            scr.draw();
        } else if (state == GameState::GAMEOVER) {
            bool restart_requested = handle_game_over(scr, in);
            if (restart_requested) {
                player = game::Player{math::Vec2{700, 300}, 0};
                asteroids = {{math::Vec2{400.0f, 400.0f}, 0, game::Asteroid::Size::LARGE}};

                state = GameState::INGAME;
            }
        }

        // SDL_Delay(60);	// TODO: Add timing logic
    }

    return 0;
}
