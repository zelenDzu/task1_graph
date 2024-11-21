#pragma once
#include <cmath>

/**
*  Получает сдвиг по X
 * @param left_orientation Стрелка смотрит слева направо
 * @param base Точка начала сдвига
 * @param offset Сдвиг
 */
inline float get_offset_x(const bool left_orientation,
                          const float base,
                          const float offset)
{
    return left_orientation ? base + offset : base - offset;
}

/**
 * Получает сдвиг по Y
 * @param left_orientation Стрелка смотрит слева направо
 * @param base Точка начала сдвига
 * @param offset Сдвиг
 */
inline float get_offset_y(const bool left_orientation,
                          const float base,
                          const float offset)
{
    return left_orientation ? base - offset : base + offset;
}