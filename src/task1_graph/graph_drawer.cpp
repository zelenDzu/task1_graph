#include <cmath>

#include "drawer/graph_drawer.h"

inline static const std::string DEFAULT_FONT{"arial.ttf"};

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

graphDrawer::graphDrawer()
{
    font.loadFromFile(DEFAULT_FONT);
}

#pragma region window_and_rendering_utilities

void graphDrawer::create_window()
{
    if (window != nullptr)
        window = nullptr;

    window = new sf::RenderWindow({1280u, 1024u}, "Main Window");
    window->setFramerateLimit(120u);
}

void graphDrawer::render()
{
    if (window == nullptr) return;

    listen();
    clear();
    display();
}

void graphDrawer::listen()
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

void graphDrawer::display() const
{
    for (const auto& [key, value] : frame.get_drawn_context())
        window->draw(*value);

    window->display();
}

void graphDrawer::clear() const
{
    window->clear();
}

#pragma endregion window_and_rendering_utilities

#pragma region drawing_api

inline static constexpr unsigned int N_ARROW_SHAPE_POINTS{7};
inline static constexpr float ARROW_HEAD_SHIFT{6.0f};
inline static constexpr float ARROW_HEAD_WIDTH_SCALE{4.0f};
inline static constexpr unsigned int FONT_SIZE{14};

unsigned int graphDrawer::draw_circle(const float radius,
                                      const float x,
                                      const float y,
                                      const sf::Color& color)
{
    const auto circle = new sf::CircleShape(radius);
    circle->setPosition(x, y);
    circle->setFillColor(color);
    return frame.push(circle);
}

unsigned int graphDrawer::draw_line(const float length,
                                    const float width,
                                    const float x,
                                    const float y,
                                    const float rotation,
                                    const sf::Color& color)
{
    const auto line = new sf::RectangleShape({length, width});
    line->setPosition({x, y});
    line->setRotation(rotation);
    line->setFillColor(color);
    return frame.push(line);
}

unsigned int graphDrawer::draw_arrow(const float xStart,
                                     const float yStart,
                                     const float xEnd,
                                     const float yEnd,
                                     const float width,
                                     const sf::Color& color)
{
    const auto arrow = new sf::ConvexShape();
    arrow->setPointCount(N_ARROW_SHAPE_POINTS);
    // The arrow is "from left to right"
    const bool left_orientation = xEnd > xStart;
    const float angle = std::atan((yEnd - yStart) / (xEnd - xStart));
    const float cos = std::cos(angle);
    const float sin = std::sin(angle);
    const float cos_angle_offset = width / 2 * cos;
    const float sin_angle_offset = width / 2 * sin;

    // Point I
    arrow->setPoint(0,
                    {
                        get_offset_x(left_orientation,
                                     xStart,
                                     cos_angle_offset),
                        get_offset_y(left_orientation,
                                     yStart,
                                     sin_angle_offset)
                    });

    // Point II
    arrow->setPoint(1,
                    {
                        get_offset_y(left_orientation,
                                     xStart,
                                     cos_angle_offset),
                        get_offset_x(left_orientation,
                                     yStart,
                                     sin_angle_offset)
                    });

    const float cos_shift_offset = ARROW_HEAD_SHIFT * cos;
    const float sin_shift_offset = ARROW_HEAD_SHIFT * sin;
    const float shifted_xEnd = get_offset_y(left_orientation,
                                            xEnd,
                                            sin_shift_offset);
    const float shifted_yEnd = get_offset_y(left_orientation,
                                            yEnd,
                                            cos_shift_offset);
    // Point(shifted_xEnd, shifted_yEnd) placed where the arrow's head started

    // Point III
    arrow->setPoint(2,
                    {
                        get_offset_y(left_orientation,
                                     shifted_xEnd,
                                     cos_angle_offset),
                        get_offset_x(left_orientation,
                                     shifted_yEnd,
                                     sin_angle_offset)
                    });

    // Point IV
    arrow->setPoint(3,
                    {
                        get_offset_y(left_orientation,
                                     shifted_xEnd,
                                     cos_angle_offset * ARROW_HEAD_WIDTH_SCALE),
                        get_offset_x(left_orientation,
                                     shifted_yEnd,
                                     sin_angle_offset * ARROW_HEAD_WIDTH_SCALE)
                    });

    // Point V
    arrow->setPoint(4, {xEnd, yEnd});

    // Point VI
    arrow->setPoint(5,
                    {
                        get_offset_x(left_orientation,
                                     shifted_xEnd,
                                     cos_angle_offset * ARROW_HEAD_WIDTH_SCALE),
                        get_offset_y(left_orientation,
                                     shifted_yEnd,
                                     sin_angle_offset * ARROW_HEAD_WIDTH_SCALE)
                    });

    // Point VII
    arrow->setPoint(6,
                    {
                        get_offset_x(left_orientation,
                                     shifted_xEnd,
                                     cos_angle_offset),
                        get_offset_y(left_orientation,
                                     shifted_yEnd,
                                     sin_angle_offset)
                    });

    arrow->setFillColor(color);
    return frame.push(arrow);
}

unsigned int graphDrawer::draw_label(const std::string& label,
                                     const float x,
                                     const float y,
                                     const sf::Color& color)
{
    const auto text = new sf::Text(label, font, FONT_SIZE);
    text->setPosition(x, y);
    text->setFillColor(color);
    return frame.push(text);
}

void graphDrawer::erase_drawing(const unsigned int id)
{
    const auto drawing = frame.get_drawable(id);
    frame.erase(id);
    delete drawing;
}

void graphDrawer::recolor_label(const unsigned int id, const sf::Color& color)
{
    frame.get_text(id)->setFillColor(color);
}

void graphDrawer::recolor_shape(const unsigned int id, const sf::Color& color)
{
    frame.get_shape(id)->setFillColor(color);
}

void graphDrawer::rename_label(const unsigned int id, const std::string& name)
{
    const auto text = frame.get_text(id);
    const auto previous_name = text->getString();
    delete previous_name.getData();
    // TODO: Check if this memory management is correct for SFML sf::String
    text->setString(name);
}

void graphDrawer::replace_shape(const unsigned int id,
                                const float x,
                                const float y)
{
    frame.get_shape(id)->setPosition(x, y);
}

#pragma endregion drawing_api
