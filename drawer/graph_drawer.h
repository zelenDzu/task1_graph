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

    graphDrawer() = default;

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
    void create_window()
    {
        if (window != nullptr)
            window = nullptr;

        window = new sf::RenderWindow({1280u, 1024u}, "Main Window");
        window->setFramerateLimit(120u);
        font.loadFromFile("arial.ttf");
    }

    void render()
    {
        if (window == nullptr) return;

        listen();
        clear();
        display();
    }

private:
    void listen()
    {
        if (window->isOpen())
        {
            for (auto event = sf::Event(); window->pollEvent(event);)
            {
                if (event.type == sf::Event::Closed)
                {
                    shutdownFlag = true;
                    window->close();
                    break;
                }
            }
        }
    }

    void display() const
    {
        for (const auto& [key, value] : frame.get_drawn_context())
            window->draw(*value);

        window->display();
    }

    void clear() const
    {
        window->clear();
    }

#pragma endregion window_and_rendering_utilities

#pragma region drawing_api
#define N_ARROW_SHAPE_POINTS 7
#define ARROW_HEAD_SHIFT 6.0f
#define FONT_SIZE 14

public:
    unsigned int drawCircle(const float radius,
                            const float x,
                            const float y,
                            const sf::Color& color)
    {
        auto circle = new sf::CircleShape(radius);
        circle->setPosition(x, y);
        circle->setFillColor(color);
        return frame.push(circle);
    }

    unsigned int drawLine(const float length,
                          const float width,
                          const float x,
                          const float y,
                          const float rotation,
                          const sf::Color& color)
    {
        auto line = new sf::RectangleShape({length, width});
        line->setPosition({x, y});
        line->setRotation(rotation);
        line->setFillColor(color);
        return frame.push(line);
    }

    unsigned int drawArrow(const float xStart,
                           const float yStart,
                           const float xEnd,
                           const float yEnd,
                           const float width,
                           const sf::Color& color)
    {
        auto arrow = new sf::ConvexShape();
        arrow->setPointCount(N_ARROW_SHAPE_POINTS);
        // TODO: Сформировать фигуру для рендера стрелки
        arrow->setPoint(0, {xStart - width / 2, yStart - width / 2});
        arrow->setPoint(1, {xStart + width / 2, yStart + width / 2});
        arrow->setPoint(2, {xStart - width / 2, yStart - width / 2});
        arrow->setPoint(3, {xEnd - width / 2, yEnd - width / 2});
        arrow->setPoint(4, {xEnd - width / 2, yEnd - width / 2});
        arrow->setPoint(5, {xEnd - width / 2, yEnd - width / 2});
        arrow->setPoint(6, {xEnd - width / 2, yEnd - width / 2});
        arrow->setFillColor(color);
        return frame.push(arrow);
    }

    unsigned int drawLabel(const std::string& label,
                           const float x,
                           const float y,
                           const sf::Color& color)
    {
        auto text = new sf::Text(label, font, FONT_SIZE);
        text->setPosition(x, y);
        text->setFillColor(color);
        return frame.push(text);
    }
#pragma endregion drawing_api
};
