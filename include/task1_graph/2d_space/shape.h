#pragma once
#include <cmath>

#include "point.h"
#include <string>
#include <vector>

/**
 * Get the X-axes applied offset
 * @param left_orientation The arrow is from left to right
 * @param base The basic point to offset
 * @param offset Offset
 * @return Applied X-offset to basic point
 */
inline float get_offset_x(const bool left_orientation,
                          const float base,
                          const float offset)
{
    return left_orientation ? base + offset : base - offset;
}

/**
 * Get the Y-axes applied offset
 * @param left_orientation The arrow is from left to right
 * @param base The basic point to offset
 * @param offset Offset
 * @return Applied Y-offset to basic point
 */
inline float get_offset_y(const bool left_orientation,
                          const float base,
                          const float offset)
{
    return left_orientation ? base - offset : base + offset;
}

enum shapeColor
{
    DEFAULT,
    MARKED,
};

/**
 * Фигура в 2-д пространстве
 */
struct shape2D
{
    unsigned int shape_id; //local
    unsigned int label_id; //sfml

    std::string label;
    point2D initial_point;
    shapeColor color;

    shape2D() = delete;
    
    shape2D(std::string&& label,
            const point2D initial_point)
        : label{label}
        , initial_point{initial_point}
    {
    }

    shape2D(std::string&& label,
            const point2D initial_point,
            const shapeColor color)
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

    /**
     * Получить все ассоциированные ID графических элементов
     * @return Список ассоциированных ID графических элементов
     */
    virtual std::vector<unsigned int> get_id_list() const
    {
        return {label_id};
    }
};

/**
 * Обыкновенный шейп дуги
*/
struct edgeShape : public shape2D
{
    static constexpr float LABEL_OFFSET{4.0f};

    unsigned int arrow_id; //sfml

    float width;
    point2D end_point;

    edgeShape() = delete;

    edgeShape(std::string&& label,
              const point2D initial_point,
              const point2D end_point,
              const shapeColor color,
              const float width)
        : shape2D(std::move(label), initial_point, color)
        , width{width}
        , end_point{end_point}
    {
    }

    /**
     * Определить положение метки названия.
     * @return Положене метки названия
     */
    point2D get_label_point() const override
    {
        const point2D middle_point = end_point.get_middle_point(initial_point);
        const bool left_orientation = end_point.x > initial_point.x;
        const float angle = std::atan(
            (end_point.y - initial_point.y) / (end_point.x - initial_point.x));
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);
        const float cos_angle_offset = LABEL_OFFSET * cos; // r * cos - polar
        const float sin_angle_offset = LABEL_OFFSET * sin;
        return {
            get_offset_y(left_orientation,
                         middle_point.x,
                         cos_angle_offset),
            get_offset_x(left_orientation,
                         middle_point.y,
                         sin_angle_offset)
        };
    }

    /**
     * Получить все ассоциированные ID графических элементов
     * @return Список ассоциированных ID графических элементов
     */
    std::vector<unsigned int> get_id_list() const override
    {
        return {label_id, arrow_id};
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
                    const shapeColor color,
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
                                         const shapeColor color,
                                         const float width)
    {
        // The arrow is "from left to right"
        const bool left_orientation = end_point.x > initial_point.x;
        const float angle = std::atan(
            (end_point.y - initial_point.y) / (end_point.x - initial_point.x));
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);
        const float cos_angle_offset = SHIFT_BETWEEN_EDGES / 2 * cos;
        const float sin_angle_offset = SHIFT_BETWEEN_EDGES / 2 * sin;

        const float xStart = get_offset_y(left_orientation,
                                          initial_point.x,
                                          cos_angle_offset);
        const float yStart = get_offset_x(left_orientation,
                                          initial_point.y,
                                          sin_angle_offset);
        const float xEnd = get_offset_y(left_orientation,
                                        end_point.x,
                                        cos_angle_offset);
        const float yEnd = get_offset_x(left_orientation,
                                        end_point.y,
                                        sin_angle_offset);

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
                                          const shapeColor color,
                                          const float width)
    {
        // The arrow is "from left to right"
        const bool left_orientation = end_point.x > initial_point.x;
        const float angle = std::atan(
            (end_point.y - initial_point.y) / (end_point.x - initial_point.x));
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);
        const float cos_angle_offset = SHIFT_BETWEEN_EDGES / 2 * cos;
        const float sin_angle_offset = SHIFT_BETWEEN_EDGES / 2 * sin;

        const float xEnd = get_offset_x(left_orientation,
                                        initial_point.x,
                                        cos_angle_offset);
        const float yEnd = get_offset_y(left_orientation,
                                        initial_point.y,
                                        sin_angle_offset);
        const float xStart = get_offset_x(left_orientation,
                                          end_point.x,
                                          cos_angle_offset);
        const float yStart = get_offset_y(left_orientation,
                                          end_point.y,
                                          sin_angle_offset);

        return {
            std::move(label), {xStart, yStart},
            {xEnd, yEnd}, color, width
        };
    }

    /**
     * Определить положение метки названия. По умолчанию middle_point
     * @return Положене метки названия
     */
    point2D get_label_point() const override
    {
        return this->end_point.get_middle_point(this->initial_point);
    }

    /**
     * Получить все ассоциированные ID графических элементов
     * @return Список ассоциированных ID графических элементов
     */
    std::vector<unsigned int> get_id_list() const override
    {
        return {
            label_id, forward.label_id, forward.arrow_id, backward.label_id,
            backward.arrow_id
        };
    }
};

/**
 * Обыкновенный шейп нода
 */
struct nodeShape final : public shape2D
{
    unsigned int circle_id; //sfml

    float radius;

    nodeShape() = delete;

    nodeShape(std::string&& label,
              const point2D initial_point,
              const shapeColor color,
              const float radius)
        : shape2D(std::move(label), initial_point, color)
        , radius{radius}
    {
    }

    /**
     * Получить все ассоциированные ID графических элементов
     * @return Список ассоциированных ID графических элементов
     */
    std::vector<unsigned int> get_id_list() const override
    {
        return {label_id, circle_id};
    }
};
