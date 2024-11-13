#pragma once
#include <vector>
#include <cstdarg>

#include "drawer_command.h"
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

    void push_command(const drawerCommand* command)
    {
        drawing_cache.push_back(command);
    }

    void clear_cache() { drawing_cache.clear(); }

public:
    static graphDrawerEngine& get_instance()
    {
        static graphDrawerEngine INSTANCE;
        return INSTANCE;
    }

    void set_graph_drawer(graphDrawer& drawer)
    {
        this->drawer = &drawer;
    }

    unsigned long add_shape(shape2D* shape)
    {
        shape_context[++last_index] = shape;
        return last_index;
    }

    graphDrawerEngine* with_commands(const unsigned int n_args,
                                     const drawerCommand* commands,
                                     ...)
    {
        va_list args;
        va_start(args, commands);
        for (unsigned int i = 0; i < n_args; i++)
        {
            // добавляем команду в кэш нашего движка рисовальщика
            const drawerCommand* command = va_arg(args, const drawerCommand*);
            push_command(command);
        }
        va_end(args);
        return this;
    }

    void step()
    {
        if (drawer->shutdownFlag)
        {
            // TODO: Завершение работы
            return;
        }

        for (const auto& command : drawing_cache)
        {
            command->execute();
        }
        clear_cache();
        drawer->render();
    }
};
