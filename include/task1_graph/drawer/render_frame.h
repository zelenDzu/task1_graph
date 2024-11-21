#pragma once
#include <map>

// хранилище графических sfml примитивов
class renderFrame
{
    unsigned int last_index{0};
    std::map<unsigned int, sf::Drawable*> drawn_context;

public:

    unsigned int get_last_index() const
    {
        return last_index;
    }

    sf::Drawable* get_drawable(const unsigned int id)
    {
        return drawn_context[id];
    }

    sf::Text* get_text(const unsigned int id)
    {
        return dynamic_cast<sf::Text*>(drawn_context[id]);
    }

    sf::Shape* get_shape(const unsigned int id)
    {
        return dynamic_cast<sf::Shape*>(drawn_context[id]);
    }

    unsigned int push(sf::Drawable* drawable)
    {
        drawn_context[++last_index] = drawable;
        return last_index;
    }

    void erase(const unsigned int id)
    {
        if (drawn_context.find(id) != drawn_context.end())
            drawn_context.erase(id);
    }

    const std::map<unsigned int, sf::Drawable*>& get_drawn_context() const
    {
        return drawn_context;
    }
};
