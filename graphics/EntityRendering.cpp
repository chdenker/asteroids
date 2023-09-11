#include "EntityRendering.h"

#include "../Constants.h"

namespace graphics {

void render_player(Screen& scr, game::Player& p)
{
    // TODO: Draw a triangle instead
    // scr.render_rectangle(p.x, p.y, consts::PLAYER_WIDTH, consts::PLAYER_HEIGHT, { 255, 255, 255 });
    scr.render_triangle();
}

void render_asteroid(Screen& scr, game::Asteroid& ast)
{
    scr.render_rectangle(ast.x, ast.y, 100, 100, { 255, 0, 0 });
}

} // namespace graphics