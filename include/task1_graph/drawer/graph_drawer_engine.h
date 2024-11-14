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
    std::vector<const drawerCommand*> drawing_cache;

    std::map<unsigned int, shape2D*> shape_context;

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

    unsigned int add_shape(shape2D* shape);

    graphDrawerEngine* with_commands(unsigned int n_args,
                                     const drawerCommand* commands,
                                     ...);

    void step();
};
