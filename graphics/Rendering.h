#ifndef RENDERING_H
#define RENDERING_H

#include "Screen.h"

#include "../game/Asteroid.h"
#include "../game/Player.h"

#include <string>

namespace graphics {

void render_text(Screen& scr, math::Vec2 pos, Color col, std::string text);

void render_hud(Screen& scr, game::Player& player);

void render_hitbox(Screen& scr, game::Hitbox h, Color col);

// Entities
void render_player(Screen& scr, game::Player& p);
void render_asteroid(Screen& scr, game::Asteroid& ast);

} // namespace graphics

#endif