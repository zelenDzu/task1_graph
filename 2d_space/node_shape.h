#pragma once

#include "shape.h"

/**
 * Обыкновенный шейп нода
 */
struct nodeShape : public shape2D
{
    double radius;

    nodeShape() = delete;

    nodeShape(std::string* label, point2D initial_point, int color, int radius) : shape2D(label, initial_point, color), radius{radius} {}

    ~nodeShape() = default;
};