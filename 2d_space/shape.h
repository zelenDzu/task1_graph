#pragma once
#include "point.h"
#include <string>

/**
 * Фигура в 2-д пространстве
 */
struct shape2D
{
    unsigned int shape_id;

    std::string* label;
    point2D initial_point;
    int color;

    shape2D() = delete;

    shape2D(std::string* label, point2D initial_point)
        : label{label}
        , initial_point{initial_point}
    {
    }

    shape2D(std::string* label, point2D initial_point, int color)
        : label{label}
        , initial_point{initial_point}
        , color{color}
    {
    }

    virtual ~shape2D() { delete label; }

    /**
     * Определить положение метки названия. По умолчанию initial_point
     * @return Положене метки названия
     */
    virtual point2D get_label_point() const
    {
        return initial_point;
    }
};
