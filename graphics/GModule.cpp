#include "GModule.h"

#include "../Constants.h"

#include <cstdio>
#include <cstdlib>

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

    if (TTF_Init() != 0) {
        std::fprintf(stderr, "GModule ctor: TTF Initialization failed %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        std::exit(-1);
    }

    font = TTF_OpenFont(consts::FONT_PATH, consts::FONT_SIZE);
    if (font == nullptr) {
        std::fprintf(stderr, "GModule ctor: TTF Font Loading failed %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        std::exit(-1);
    }
}

GModule::~GModule()
{
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GModule::clear(int red, int green, int blue)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void GModule::render_text(int x, int y, std::uint8_t red, std::uint8_t green, std::uint8_t blue, char const* text)
{
    SDL_Color color{red, green, blue, SDL_ALPHA_OPAQUE};
    SDL_Surface* surf = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    // TODO: (Possible performance improvement) Move this outside render_text
    int tex_w = 0;
    int tex_h = 0;
    SDL_QueryTexture(tex, nullptr, nullptr, &tex_w, &tex_h);
    SDL_Rect dstrect{x, y, tex_w, tex_h};

    SDL_RenderCopy(renderer, tex, nullptr, &dstrect);

    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
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

void GModule::render_unfilled_rectangle(int x, int y, int width, int height, int red, int green, int blue)
{
    SDL_Rect rect{ x, y, width, height };
	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);    
}

void GModule::render_circle(int x0, int y0, int radius, int red, int green, int blue)
{
	// Midpoint circle algorithm
	// Shamelessly copied from https://en.wikipedia.org/w/index.php?title=Midpoint_circle_algorithm&oldid=889172082#C_example
	int x = radius - 1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);

	SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
    while (x >= y) {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void GModule::draw()
{
    SDL_RenderPresent(renderer);
}
