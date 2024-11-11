#pragma once

#include "shape.h"

/**
 * Обыкновенный шейп нода
 */
struct nodeShape final : public shape2D
{
    float radius;

    nodeShape() = delete;

    nodeShape(std::string* label,
              const point2D initial_point,
              const int color,
              const float radius)
        : shape2D(label, initial_point, color)
        , radius{radius}
    {
    }
};
