#pragma once
#include <cmath>

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