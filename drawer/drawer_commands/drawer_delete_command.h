#pragma once
#include "drawer_command.h"

struct drawerDeleteCommand : public drawerCommand
{
    unsigned long shape_id;

    drawerDeleteCommand() = delete;

    drawerDeleteCommand(graphDrawerEngine* engine, const unsigned long shape_id) : drawerCommand(engine), shape_id{shape_id} {}

    ~drawerDeleteCommand() = default;

    virtual void execute() const override
    {
        // TODO: Реализация команды на удаление нужного шейпа
        // Как делать? Берёшь местный graphDrawerEngine, и работаешь через его graphDrawer.
    }
};