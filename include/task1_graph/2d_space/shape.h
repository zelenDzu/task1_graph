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

    shape2D(std::string* label,
            const point2D initial_point)
        : label{label}
        , initial_point{initial_point}
    {
    }

    shape2D(std::string* label,
            const point2D initial_point,
            const int color)
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

/**
 * Обыкновенный шейп дуги
*/
struct edgeShape final : public shape2D
{
    float width;
    point2D end_point;

    edgeShape() = delete;

    edgeShape(std::string* label,
              const point2D initial_point,
              const point2D end_point,
              const int color,
              const float width)
        : shape2D(label, initial_point, color)
        , end_point{end_point}
        , width{width}
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
