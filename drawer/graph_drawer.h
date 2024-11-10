#pragma once
//include sfml


/**
 * Класс-рисовальщик. Сюда заносишь код чисто под SFML и работу с внешней библиотекой. Этот класс просто должен рисовать примитивы.
 */
class graphDrawer
{
private:

    graphDrawer() = default;

    ~graphDrawer() = default;

public:
    /**
     * Расстояние между парой из двух дуг
     */
    static const int SHIFT_BETWEEN_EDGES = 6;

    static graphDrawer& get_instance() 
    {
        static graphDrawer INSTANCE;
        return INSTANCE;
    }

    // draw circle (x, y, r, color)
    // draw line (color, point,...)
    // draw label
};