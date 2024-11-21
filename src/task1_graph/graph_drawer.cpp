#include "2d_space/geometry_resolver.h"
#include "drawer/graph_drawer.h"

inline static const std::string DEFAULT_FONT{"arial.ttf"};

graphDrawer::graphDrawer()
{
    font.loadFromFile(DEFAULT_FONT);
}

#pragma region window_and_rendering_utilities
#define WINDOW_WIDTH 1280u
#define WINDOW_MAX_WIDTH 1280.f
#define Y_INVERT(n) (WINDOW_MAX_WIDTH - n)
#define WINDOW_HEIGHT 1024u
#define PI 3.1415f

void graphDrawer::create_window()
{
    if (window != nullptr)
        window = nullptr;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // ������� �����������
    window = new sf::RenderWindow({WINDOW_WIDTH, WINDOW_HEIGHT},
                                  "Main Window",
                                  sf::Style::Default,
                                  settings);
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

inline static constexpr unsigned int N_ARROW_SHAPE_POINTS{9};
inline static constexpr float ARROW_HEAD_SHIFT{40.0f};
inline static constexpr float ARROW_HEAD_WIDTH_SCALE{5.0f};
inline static constexpr unsigned int FONT_SIZE{28};

unsigned int graphDrawer::draw_circle(const float radius,
                                      const float x,
                                      const float y,
                                      const sf::Color& color)
{
    const auto circle = new sf::CircleShape(radius);
    circle->setOrigin(radius, radius);

    circle->setPosition(x, Y_INVERT(y));
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
    line->setPosition({x, Y_INVERT(y)});
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
    auto* arrow = new sf::VertexArray(sf::Triangles, N_ARROW_SHAPE_POINTS);
    const bool left_orientation = xEnd > xStart;
    const float angle = PI / 2 - std::atan(
        (yEnd - yStart) / (xEnd - xStart));
    const float cos = std::cos(angle);
    const float sin = std::sin(angle);
    const float cos_angle_offset = width / 2 * cos;
    const float sin_angle_offset = width / 2 * sin;

    // Point I
    (*arrow)[0].position =
    {
        get_offset_x(left_orientation,
                     xStart,
                     cos_angle_offset),
        Y_INVERT(get_offset_y(left_orientation,
            yStart,
            sin_angle_offset))
    };
    // Point II
    (*arrow)[1].position =
    {
        get_offset_y(left_orientation,
                     xStart,
                     cos_angle_offset),
        Y_INVERT(get_offset_x(left_orientation,
            yStart,
            sin_angle_offset))
    };

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
    (*arrow)[2].position =
    {
        get_offset_y(left_orientation,
                     shifted_xEnd,
                     cos_angle_offset),
        Y_INVERT(get_offset_x(left_orientation,
            shifted_yEnd,
            sin_angle_offset))
    };

    (*arrow)[3].position = (*arrow)[0].position;
    (*arrow)[4].position = (*arrow)[2].position;

    // Point IV
    (*arrow)[6].position =
    {
        get_offset_y(left_orientation,
                     shifted_xEnd,
                     cos_angle_offset * ARROW_HEAD_WIDTH_SCALE),
        Y_INVERT(get_offset_x(left_orientation,
            shifted_yEnd,
            sin_angle_offset * ARROW_HEAD_WIDTH_SCALE))
    };

    // Point V
    (*arrow)[7].position = {xEnd, Y_INVERT(yEnd)};

    // Point VI
    (*arrow)[8].position =
    {
        get_offset_x(left_orientation,
                     shifted_xEnd,
                     cos_angle_offset * ARROW_HEAD_WIDTH_SCALE),
        Y_INVERT(get_offset_y(left_orientation,
            shifted_yEnd,
            sin_angle_offset * ARROW_HEAD_WIDTH_SCALE))
    };

    // Point VII
    (*arrow)[5].position =
    {
        get_offset_x(left_orientation,
                     shifted_xEnd,
                     cos_angle_offset),
        Y_INVERT(get_offset_y(left_orientation,
            shifted_yEnd,
            sin_angle_offset))
    };

    for (unsigned int i = 0u; i < N_ARROW_SHAPE_POINTS; i++)
        (*arrow)[i].color = color;
    return frame.push(arrow);
}

unsigned int graphDrawer::draw_label(const std::string& label,
                                     const float x,
                                     const float y,
                                     const sf::Color& color)
{
    const auto text = new sf::Text(label, font, FONT_SIZE);
    text->setPosition(x, Y_INVERT(y));
    const sf::FloatRect rc = text->getLocalBounds();
    text->setOrigin(rc.width / 2, rc.height);
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

void graphDrawer::recolor_arrow(const unsigned int id, const sf::Color& color)
{
    for (unsigned int i = 0u; i < N_ARROW_SHAPE_POINTS; i++)
        (*frame.get_vertex_array(id))[i].color = color;
}

void graphDrawer::rename_label(const unsigned int id, const std::string& name)
{
    const auto text = frame.get_text(id);
    text->setString(name);
}

void graphDrawer::replace_shape(const unsigned int id,
                                const float x,
                                const float y)
{
    frame.get_shape(id)->setPosition(x, y);
}

#pragma endregion drawing_api
