#pragma once
#include "2d_space/shape.h"

class graphDrawerEngine;

/**
 * Команда, которая выполняется на движке
 */
struct drawerCommand
{
    graphDrawerEngine* engine;

    drawerCommand() = delete;

    drawerCommand(graphDrawerEngine* engine)
        : engine{engine}
    {
    }

    virtual ~drawerCommand() = default;

    virtual void execute() const = 0;
};

struct drawerCreateCommand : public drawerCommand
{
    shape2D& shape_to_create;

    drawerCreateCommand() = delete;

    drawerCreateCommand(graphDrawerEngine* engine, shape2D& shape_to_create)
        : drawerCommand(engine)
        , shape_to_create{shape_to_create}
    {
    }

    void execute() const override;
};

struct drawerDeleteCommand : public drawerCommand
{
    unsigned int shape_id;

    drawerDeleteCommand() = delete;

    drawerDeleteCommand(graphDrawerEngine* engine, const unsigned int shape_id)
        : drawerCommand(engine)
        , shape_id{shape_id}
    {
    }

    void execute() const override;
};

struct drawerRecolorCommand : public drawerCommand
{
    unsigned int shape_id;
    int* color;

    drawerRecolorCommand() = delete;

    drawerRecolorCommand(graphDrawerEngine* engine,
                         const unsigned int shape_id,
                         int* color)
        : drawerCommand(engine)
        , shape_id{shape_id}
        , color{color}
    {
    }

    void execute() const override;
};
