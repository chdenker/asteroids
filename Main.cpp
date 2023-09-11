#include "Constants.h"

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

int main()
{
    std::unique_ptr<GModule> gmod = std::make_unique<GModule>(consts::SCR_WIDTH, consts::SCR_HEIGHT);
    graphics::Screen scr{consts::SCR_WIDTH, consts::SCR_HEIGHT, std::move(gmod)};
    Input in{};

    game::Player player{500, 300, 0};
    std::vector<game::Asteroid> asteroids{};
    asteroids.reserve(consts::MAX_ASTEROIDS);

	asteroids.emplace_back(400, 400, 0);

    game_running = true;
    while (game_running) {
        process_input(in);

        scr.clear({0, 0, 0});

        graphics::render_player(scr, player);
        for (auto& a : asteroids) graphics::render_asteroid(scr, a);

        scr.draw();
    }

    return 0;
}