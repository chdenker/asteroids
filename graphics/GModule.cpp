#include "GModule.h"

#include "../Constants.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <cstdlib>
#include <array>

GModule::GModule(int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::fprintf(stderr, "screen_init: %s\n", SDL_GetError());
		std::exit(-1);
	}

	window = SDL_CreateWindow(consts::GAME_TITLE, 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::fprintf(stderr, "screen_init: %s\n", SDL_GetError());
		SDL_Quit();
		std::exit(-1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::fprintf(stderr, "screen_init: %s\n", SDL_GetError());
		SDL_Quit();
		std::exit(-1);
	}
}

GModule::~GModule()
{
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GModule::clear(int red, int green, int blue)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void GModule::render_line(int x1, int y1, int x2, int y2, int red, int green, int blue)
{
	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void GModule::render_rectangle(int x, int y, int width, int height, int red, int green, int blue)
{
    SDL_Rect rect{ x, y, width, height };
	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
}

void GModule::draw()
{
    SDL_RenderPresent(renderer);
}
