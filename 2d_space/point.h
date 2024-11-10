#pragma once

/**
 * Точка в 2д пространстве
 */
struct point2D final
{
    const int x;
    const int y;

    point2D() = delete; // запрет писать пустую конструкцию

    point2D(int x, int y) : x{x}, y{y} {}

    ~point2D() = default;

    /**
     * Получить среднюю точку на отрезке
     * @param other Конец отрезка
     * @returns Средняя точка
     */
    const point2D get_middle_point(point2D other) const //означает что ничего не изменяется внутри метода
    {
        point2D middle_point = point2D(other.x - x, other.y - y);
        return middle_point;
    }
};
