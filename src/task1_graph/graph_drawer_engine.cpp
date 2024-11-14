#include "drawer/graph_drawer_engine.h"

void graphDrawerEngine::push_command(const drawerCommand* command)
{
    drawing_cache.push_back(command);
}

void graphDrawerEngine::clear_cache()
{
    drawing_cache.clear();
}

void graphDrawerEngine::set_graph_drawer(graphDrawer& drawer)
{
    this->drawer = &drawer;
}

unsigned int graphDrawerEngine::add_shape(shape2D* shape)
{
    shape_context[++last_index] = shape;
    return last_index;
}

graphDrawerEngine* graphDrawerEngine::with_commands(const unsigned int n_args,
                                                    const drawerCommand*
                                                    commands,
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

void graphDrawerEngine::step()
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