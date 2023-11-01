#include "Constants.h"

#include "game/Player.h"
#include "game/Asteroid.h"

#include "graphics/Screen.h"
#include "graphics/GModule.h"
#include "graphics/EntityRendering.h"

#include <SDL2/SDL.h>

#include <memory>
#include <vector>
#include <cmath>

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

	math::Vec2& pos = player.pos;
	math::Vec2& dir = player.dir;

	// Get current direction vector (dir_x,dir_y) first...
	float dir_x = 0.0f;
	float dir_y = 1.0f;
	// ... then rotate by the current angle
	double rot_cos = std::cos(player.get_angle());
    double rot_sin = std::sin(player.get_angle());
	float trans_x = rot_cos * dir_x - rot_sin * dir_y;
	float trans_y = rot_sin * dir_x + rot_cos * dir_y;

	// Apply translation
	pos.x = pos.x + consts::PLAYER_ACCELERATION * trans_x;
	pos.y = pos.y + consts::PLAYER_ACCELERATION * trans_y;

	in = Input{};	// Reset
}

int main()
{
    std::unique_ptr<GModule> gmod = std::make_unique<GModule>(consts::SCR_WIDTH, consts::SCR_HEIGHT);
    graphics::Screen scr{consts::SCR_WIDTH, consts::SCR_HEIGHT, std::move(gmod)};
    Input in{};

    game::Player player{math::Vec2{500, 300}, 0};
    std::vector<game::Asteroid> asteroids{};
    asteroids.reserve(consts::MAX_ASTEROIDS);

	asteroids.emplace_back(400, 400, 0);

    game_running = true;
    while (game_running) {
        process_input(in);

		update(in, player, asteroids);

        scr.clear({0, 0, 0});

        graphics::render_player(scr, player);
        for (auto& a : asteroids) graphics::render_asteroid(scr, a);

        scr.draw();
		SDL_Delay(60);	// TODO: Add timing logic
    }

    return 0;
}