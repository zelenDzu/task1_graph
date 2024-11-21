#pragma once
#include <cmath>

/**
*  �������� ����� �� X
 * @param left_orientation ������� ������� ����� �������
 * @param base ����� ������ ������
 * @param offset �����
 */
inline float get_offset_x(const bool left_orientation,
                          const float base,
                          const float offset)
{
    return left_orientation ? base + offset : base - offset;
}

/**
 * �������� ����� �� Y
 * @param left_orientation ������� ������� ����� �������
 * @param base ����� ������ ������
 * @param offset �����
 */
inline float get_offset_y(const bool left_orientation,
                          const float base,
                          const float offset)
{
    return left_orientation ? base - offset : base + offset;
}