#include "Input.h"
#include "Vars.h"

#include <SDL2/SDL.h>

#include <iostream>

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
            global::hitbox_rendering = !global::hitbox_rendering;
            std::cout << "hitbox_rendering = " << global::hitbox_rendering << std::endl;
            break;
        case SDLK_ESCAPE:
            global::game_running = false;
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
        global::game_running = false;
        break;
    }
}