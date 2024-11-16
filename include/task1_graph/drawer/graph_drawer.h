#pragma once
#include <SFML/Graphics.hpp>
#include "render_frame.h"

/**
 * Renderer component
 */
class graphDrawer
{
    renderFrame frame{};

    sf::RenderWindow* window = nullptr;

    sf::Font font;

    graphDrawer();

    ~graphDrawer() = default;

public:
    /**
     * Расстояние между парой из двух дуг
     */
    static constexpr float SHIFT_BETWEEN_EDGES = 6.0f;

    static graphDrawer& get_instance()
    {
        static graphDrawer INSTANCE;
        return INSTANCE;
    }

    bool shutdownFlag{false};

#pragma region window_and_rendering_utilities

public:
    void create_window();

    void render();

private:
    void listen();

    void display() const;

    void clear() const;

#pragma endregion window_and_rendering_utilities

#pragma region drawing_api

public:
    unsigned int draw_circle(float radius,
                             float x,
                             float y,
                             const sf::Color& color = sf::Color::Yellow);

    unsigned int draw_line(float length,
                           float width,
                           float x,
                           float y,
                           float rotation,
                           const sf::Color& color = sf::Color::Blue);

    unsigned int draw_arrow(float xStart,
                            float yStart,
                            float xEnd,
                            float yEnd,
                            float width,
                            const sf::Color& color = sf::Color::Blue);

    unsigned int draw_label(const std::string& label,
                            float x,
                            float y,
                            const sf::Color& color = sf::Color::Magenta);

    void erase_drawing(unsigned int id);

    void recolor_label(unsigned int id, const sf::Color& color);

    void recolor_shape(unsigned int id, const sf::Color& color);

    void rename_label(unsigned int id, const std::string& name);

    void replace_shape(unsigned int id, float x, float y);

#pragma endregion drawing_api
};
