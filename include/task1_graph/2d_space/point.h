#pragma once

/**
 * Точка в 2д пространстве
 */
struct point2D final
{
    const float x;
    const float y;

    point2D() = delete;

    point2D(const float x, const float y)
        : x{x}
        , y{y}
    {
    }

    ~point2D() = default;

    /**
     * Получить среднюю точку на отрезке
     * @param other Конец отрезка
     * @returns Средняя точка
     */
    point2D get_middle_point(const point2D other) const
    {
        return {(other.x + x) / 2, (other.y + y) / 2};
    }
};
