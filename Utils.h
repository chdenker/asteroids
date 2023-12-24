#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

using uint = std::uint32_t;

namespace math {

class Vec2 {
public:
    float x;
    float y;

    void rotate(double angle);
};

} // namespace math

#endif