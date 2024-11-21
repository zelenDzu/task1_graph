#include "drawer/graph_drawer_engine.h"

#define DRAWER_IS_ABSENT_ERROR_CODE 2

void graphDrawerEngine::push_command(const drawerCommand* command)
{
    drawing_cache.push_back(command);
}

void graphDrawerEngine::clear_cache()
{
    for (const drawerCommand* command : drawing_cache)
    {
        delete command;
    }
    drawing_cache.clear();
}

void graphDrawerEngine::set_graph_drawer(graphDrawer& drawer)
{
    this->drawer = &drawer;
}

graphDrawer& graphDrawerEngine::get_graph_drawer() const
{
    if (drawer == nullptr)
        throw DRAWER_IS_ABSENT_ERROR_CODE;

    return *drawer;
}

unsigned int graphDrawerEngine::add_shape(shape2D* shape)
{
    shape_context[++last_index] = shape;
    return last_index;
}

unsigned int graphDrawerEngine::get_shape_label_id(const unsigned int index)
{
    return shape_context[index]->label_id;
}

shape2D* graphDrawerEngine::get_shape(const unsigned int index)
{
    return shape_context[index];
}

void graphDrawerEngine::remove_shape(const unsigned int index)
{
    shape_context.erase(index);
}

graphDrawerEngine* graphDrawerEngine::with_commands(std::vector<const drawerCommand*>&& commands)
{
    for (const drawerCommand* command : commands)
    {
        // добавляем команду в кэш нашего движка рисовальщика
        push_command(command);
    }
    return this;
}

void graphDrawerEngine::step()
{
    // если в sfml закрыли окно
    if (drawer->shutdownFlag)
    {
        clear_cache();
        last_index = 0u;
        drawer = nullptr;
        return;
    }

    for (const drawerCommand* command : drawing_cache)
    {
        command->execute();
    }
    clear_cache();
    drawer->render();
}
