#pragma once
#include "point.h"
#include <string>

/**
 * Фигура в 2-д пространстве
 */
struct shape2D
{
    unsigned int shape_id;

    std::string label;
    point2D initial_point;
    int color;

    shape2D() = delete;

    shape2D(std::string&& label,
            const point2D initial_point)
        : label{label}
        , initial_point{initial_point}
    {
    }

    shape2D(std::string&& label,
            const point2D initial_point,
            const int color)
        : label{label}
        , initial_point{initial_point}
        , color{color}
    {
    }

    virtual ~shape2D() noexcept = default;

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
struct edgeShape : public shape2D
{
    float width;
    point2D end_point;

    edgeShape() = delete;

    edgeShape(std::string&& label,
              const point2D initial_point,
              const point2D end_point,
              const int color,
              const float width)
        : shape2D(std::move(label), initial_point, color)
        , width{width}
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

struct doubleEdgeShape : public edgeShape
{
    static constexpr float SHIFT_BETWEEN_EDGES{6.0f};
    edgeShape forward;
    edgeShape backward;

    doubleEdgeShape() = delete;

    doubleEdgeShape(std::string&& label,
                    const point2D initial_point,
                    const point2D end_point,
                    const int color,
                    const float width,
                    std::string&& forward_label,
                    std::string&& backward_label)
        : edgeShape(std::move(label), initial_point, end_point, color, width)
        , forward{
            create_forward_edge(std::move(forward_label),
                                initial_point,
                                end_point,
                                color,
                                width)
        }
        , backward{
            create_backward_edge(std::move(backward_label),
                                 initial_point,
                                 end_point,
                                 color,
                                 width)
        }
    {
    }

    /**
     * Изготавливает сдвинутый шейп прямой дуги от старта к концу
     * @param label Надпись для прямой дуги
     * @param initial_point Начальная точка целого шейпа
     * @param end_point Конечная точка целого шейпа
     * @param color Цвет
     * @param width Ширина
     * @return Дуга от старта к концу
     */
    static edgeShape create_forward_edge(std::string&& label,
                                         const point2D initial_point,
                                         const point2D end_point,
                                         const int color,
                                         const float width)
    {
        const float xStart = 0.0f;
        const float yStart = 0.0f;
        const float xEnd = 1.0f;
        const float yEnd = 1.0f;

        return {
            std::move(label), {xStart, yStart},
            {xEnd, yEnd}, color, width
        };
    }

    /**
     * Изготавливает сдвинутый шейп обратной дуги от конца к началу
     * @param label Надпись для обратной дуги
     * @param initial_point Начальная точка целого шейпа
     * @param end_point Конечная точка целого шейпа
     * @param color Цвет
     * @param width Ширина
     * @return Дуга от конца к началу
     */
    static edgeShape create_backward_edge(std::string&& label,
                                          const point2D initial_point,
                                          const point2D end_point,
                                          const int color,
                                          const float width)
    {
        const float xStart = 0.0f;
        const float yStart = 0.0f;
        const float xEnd = 1.0f;
        const float yEnd = 1.0f;

        return {
            std::move(label), {xStart, yStart},
            {xEnd, yEnd}, color, width
        };
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

    nodeShape(std::string&& label,
              const point2D initial_point,
              const int color,
              const float radius)
        : shape2D(std::move(label), initial_point, color)
        , radius{radius}
    {
    }
};
