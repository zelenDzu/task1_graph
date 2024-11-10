#pragma once
#include "drawer_command.h"

struct drawerCreateCommand : public drawerCommand
{

    shape2D* shape_to_create;

    drawerCreateCommand() = delete;

    drawerCreateCommand(graphDrawerEngine* engine, shape2D* shape_to_create) : drawerCommand(engine), shape_to_create{shape_to_create} {}

    ~drawerCreateCommand() = default;

    virtual void execute() const override
    {
        // обращаюсь к engine.drawer и говорю ему рисовать, даю уже готовые точки, цвета,... или сразу shape
        // 
        // TODO: Реализация команды на создание нужного шейпа
        // Как делать? Берёшь местный graphDrawerEngine, и работаешь через его graphDrawer.
        // Нужно присвоить новый уникальный id-шник с помощью метода add_shape
        engine->add_shape(shape_to_create);
    }
};