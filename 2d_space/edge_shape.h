#pragma once

#include "shape.h"

/**
 * Обыкновенный шейп дуги
*/
struct edgeShape final : public shape2D
{
    point2D end_point;

    edgeShape() = delete;

    edgeShape(std::string* label,
              const point2D initial_point,
              const point2D end_point,
              const int color)
        : shape2D(label, initial_point, color)
        , end_point{end_point}
    {
    }

    /**
     * Определить положение метки названия. По умолчанию initial_point
     * @return Положене метки названия
     */
    point2D get_label_point() const override
    {
        return this->end_point.get_middle_point(this->initial_point);
    }
};
