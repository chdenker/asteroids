#include "Constants.h"

#include "game/Hitbox.h"
#include "game/Player.h"
#include "game/Asteroid.h"

#include "graphics/Screen.h"
#include "graphics/GModule.h"
#include "graphics/EntityRendering.h"

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

bool game_running = false;

struct Input {
    bool left;
    bool right;
    bool up;
    bool down;
    bool space;
};

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
		case SDLK_ESCAPE:
			game_running = false;
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
	return (a.pos.x < b.pos.x + b.width) && (a.pos.x + a.width > b.pos.x) 
		&& (a.pos.y < b.pos.y + b.height) && (a.pos.y + a.height > b.pos.y);
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
	for (auto const& ast : asteroids) {
		game::Hitbox ast_hbox = ast.get_hitbox();
		if (collides_with(player_hbox, ast_hbox)) {
			// TODO: Game over
		}
		for (game::Rocket& r : player.rockets) {
			game::Hitbox r_hbox = r.get_hitbox();
			if (collides_with(r_hbox, ast_hbox)) {
				// TODO: Destroy asteroid and rocket, add points to player's score
				player.score += consts::ASTEROID_SCORE;
				r.exploded = true;
			}
		}
	}

	in = Input{};	// Reset
}

int main()
{
    std::unique_ptr<GModule> gmod = std::make_unique<GModule>(consts::SCR_WIDTH, consts::SCR_HEIGHT);
    graphics::Screen scr{consts::SCR_WIDTH, consts::SCR_HEIGHT, std::move(gmod)};
    Input in{};

    // game::Player player{math::Vec2{500, 300}, 0};
    game::Player player{math::Vec2{700, 300}, 0};
    std::vector<game::Asteroid> asteroids{};
    asteroids.reserve(consts::MAX_ASTEROIDS);

    asteroids.emplace_back(math::Vec2{400.0f, 400.0f}, 0, game::Asteroid::Size::LARGE);

    game_running = true;
    while (game_running) {
        process_input(in);

        update(in, player, asteroids);

        scr.clear({0, 0, 0});

        graphics::render_player(scr, player);
        for (auto& a : asteroids) graphics::render_asteroid(scr, a);

        scr.draw();
        // SDL_Delay(60);	// TODO: Add timing logic
    }

    return 0;
}
