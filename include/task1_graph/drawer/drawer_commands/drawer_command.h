#pragma once
#include "2d_space/shape.h"
#include <vector>

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
    const std::vector<unsigned int> shapes_id;

    drawerDeleteCommand() = delete;

    drawerDeleteCommand(graphDrawerEngine* engine,
                        std::vector<unsigned int>&& shapes_id)
        : drawerCommand(engine)
        , shapes_id{shapes_id}
    {
    }

    void execute() const override;
};

struct drawerRecolorCommand : public drawerCommand
{
    unsigned int shape_id;
    bool mark;

    drawerRecolorCommand() = delete;

    drawerRecolorCommand(graphDrawerEngine* engine,
                         const unsigned int shape_id,
                         const bool mark)
        : drawerCommand(engine)
        , shape_id{shape_id}
        , mark{mark}
    {
    }

    void execute() const override;
};

struct drawerCreateGraphCommand : public drawerCommand
{
    std::vector<nodeShape*> nodes_to_create;
    std::vector<edgeShape*> edges_to_create;

    drawerCreateGraphCommand() = delete;

    drawerCreateGraphCommand(graphDrawerEngine* engine,
                             std::vector<nodeShape*>&& nodes_to_create,
                             std::vector<edgeShape*>&& edges_to_create)
        : drawerCommand(engine)
        , nodes_to_create{nodes_to_create}
        , edges_to_create{edges_to_create}
    {
    }

    void execute() const override;
};

struct drawerUpdateLabelCommand : public drawerCommand
{
    const unsigned int shape_id;
    const std::string label;

    drawerUpdateLabelCommand() = delete;

    drawerUpdateLabelCommand(graphDrawerEngine* engine,
                             const unsigned int shape_id,
                             std::string&& label)
        : drawerCommand(engine)
        , shape_id{shape_id}
        , label{label}
    {
    }

    void execute() const override;
};
