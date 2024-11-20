#pragma once
#include <vector>
#include <cstdarg>

#include "drawer_commands/drawer_command.h"
#include "graph_drawer.h"

/**
 * Движок. Это основная точка входа, главный контроллер всего рантайма.
 */
class graphDrawerEngine
{
    std::vector<const drawerCommand*> drawing_cache{};

    std::map<unsigned int, shape2D*> shape_context{};

    graphDrawer* drawer = nullptr;

    unsigned int last_index{0};

    graphDrawerEngine() = default;

    void push_command(const drawerCommand* command);

    void clear_cache();

public:
    static graphDrawerEngine& get_instance()
    {
        static graphDrawerEngine INSTANCE;
        return INSTANCE;
    }

    void set_graph_drawer(graphDrawer& drawer);

    graphDrawer& get_graph_drawer() const;

    unsigned int add_shape(shape2D* shape);

    unsigned int get_shape_label_id(unsigned int index);

    shape2D* get_shape(unsigned int index);

    void remove_shape(unsigned int index);

    graphDrawerEngine* with_commands(std::vector<const drawerCommand*>&& commands);

    void step();
};
