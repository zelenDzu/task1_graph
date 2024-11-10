#pragma once
#include "drawer_command.h"

struct drawerRecolorCommand : public drawerCommand
{
    unsigned long shape_id;
    int *color; // Заменишь на Color, короче чё-то "цвет" из sfml

    drawerRecolorCommand() = delete;

    drawerRecolorCommand(graphDrawerEngine* engine, const unsigned long shape_id, int* color) : drawerCommand(engine), shape_id{shape_id}, color{color} {}

    ~drawerRecolorCommand() = default;

    virtual void execute() const override
    {
        // TODO: Реализация команды на обновление цвета нужного шейпа
        // Как делать? Берёшь местный graphDrawerEngine, и работаешь через его graphDrawer.
    }
};