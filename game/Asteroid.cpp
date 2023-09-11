#include "Asteroid.h"

namespace game {

Asteroid::Asteroid(uint x, uint y, uint angle, uint speed)
: x{x}, y{y}, angle{angle}, speed{speed}, size{Size::LARGE}
{}

} // namespace game