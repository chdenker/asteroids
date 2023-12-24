#include "Utils.h"

#include <cmath>

namespace math {

void Vec2::rotate(double angle)
{
    float cur_x = x;
    float cur_y = y;
    float rot_cos = std::cos(angle);
    float rot_sin = std::sin(angle);
    x = rot_cos * cur_x - rot_sin * cur_y;
    y = rot_sin * cur_x + rot_cos * cur_y;
}

} // namespace math