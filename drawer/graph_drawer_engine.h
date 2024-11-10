#pragma once
#include <vector>
#include <stdarg.h>
#include "drawer_command.h"
#include "graph_drawer.h"

/**
 * Движок. Это основная точка входа, главный контроллер всего рантайма.
 */
class graphDrawerEngine
{
private:
    std::vector<const drawerCommand*> drawing_cache;

    std::vector<shape2D*> drawing_context;

    graphDrawer* drawer;

    graphDrawerEngine()
    {
        //drawing_cache = {};
        //drawing_context = {};
    }

    ~graphDrawerEngine() 
    { 
        //delete drawing_cache;
        //delete drawing_context;
    }

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
        // TODO: Если шейпов будет много, то целочисленный тип переполнится) стандартная библиотека c++ момент
        // А ещё желательно поменять идентификатор на нормальный, а не size коллекции шейпов
        unsigned long size = drawing_context.size();
        drawing_context.push_back(shape);
        return size;
    }

    graphDrawerEngine* with_commands(const drawerCommand* commands, ...) 
    {
        // CHECK if work
        va_list args;
        va_start(args, commands);
        const drawerCommand* command = va_arg(args, const drawerCommand*);
        push_command(command); // добавляем команду в кэш нашего движка рисовальщика
        va_end(args);
        return this;
    }

    void step() 
    {
        // TODO: Проверить шаг движка, подогнать под себя. Здесь хорошо дебажить выполнение каждой команды
        for (const auto& command : drawing_cache)
        {
            command->execute();
        }
        clear_cache();
        // drawer rerender
    }
};