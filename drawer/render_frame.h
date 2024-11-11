#pragma once
#include <map>

class renderFrame
{
    unsigned int last_index{0};
    std::map<unsigned int, sf::Drawable*> drawn_context;

public:

    unsigned int get_last_index() const
    {
        return last_index;
    }

    sf::Drawable* getDrawable(const unsigned int id)
    {
        return drawn_context[id];
    }

    unsigned int push(sf::Drawable* drawable)
    {
        drawn_context[++last_index] = drawable;
        return last_index;
    }

    const std::map<unsigned int, sf::Drawable*>& get_drawn_context() const
    {
        return drawn_context;
    }
};
