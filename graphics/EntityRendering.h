#ifndef ENTITY_RENDERING_H
#define ENTITY_RENDERING_H

#include "Screen.h"

#include "../game/Asteroid.h"
#include "../game/Player.h"

namespace graphics {

void render_player(Screen& scr, game::Player& p);
void render_asteroid(Screen& scr, game::Asteroid& ast);

} // namespace graphics

#endif