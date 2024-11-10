#pragma once

#include "shape.h"

/**
 * Обыкновенный шейп дуги
*/
struct edgeShape : public shape2D
{
    point2D end_point;

    edgeShape() = delete;

    edgeShape(std::string* label, point2D initial_point, point2D end_point, int color) : shape2D(label, initial_point, color), end_point{end_point} {}

    ~edgeShape() = default;

    /**
     * Определить положение метки названия. По умолчанию initial_point
     * @return Положене метки названия
     */
    virtual const point2D get_label_point() const override
    {
        // TODO: Подложить получение позиции метки для одинарной дуги (просто сдвиг на нормальный вектор с какой-нибудь длиной)
        const point2D label_point = this->end_point.get_middle_point(this->initial_point); // добавить сдвиг, чтоб не ровно посередине дуги была)
        return label_point;
    }
};