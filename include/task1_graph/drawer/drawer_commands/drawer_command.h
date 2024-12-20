#pragma once
#include <map>

#include "2d_space/shape.h"
#include "graph/graph.h"
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

// destroy
struct drawerCreateNodeCommand : public drawerCommand
{
    nodeShape& shape_to_create;

    drawerCreateNodeCommand() = delete;

    drawerCreateNodeCommand(graphDrawerEngine* engine,
                            nodeShape& shape_to_create)
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
        , shapes_id{std::move(shapes_id)}
    {
    }

    void execute() const override;
};

struct drawerEdgeRecolorCommand : public drawerCommand
{
    unsigned int shape_id;
    edgeType edge_type;
    bool mark;

    drawerEdgeRecolorCommand() = delete;

    drawerEdgeRecolorCommand(graphDrawerEngine* engine,
                         const unsigned int shape_id,
                         const bool mark,
                         const edgeType edge_type)
        : drawerCommand(engine)
        , shape_id{shape_id}
        , edge_type{edge_type}
        , mark{mark}
    {
    }

    void execute() const override;
};

struct drawerCreateGraphCommand : public drawerCommand
{
    std::map<nodeShape*, node*> nodes_to_create;
    std::map<edgeShape*, edge*> edges_to_create;
    std::map<doubleEdgeShape*, edge*> doubleEdges_to_create;

    drawerCreateGraphCommand() = delete;

    drawerCreateGraphCommand(graphDrawerEngine* engine,
                             std::map<nodeShape*, node*>&& nodes_to_create,
                             std::map<edgeShape*, edge*>&& edges_to_create,
                             std::map<doubleEdgeShape*, edge*>&&
                             doubleEdges_to_create)
        : drawerCommand(engine)
        , nodes_to_create{std::move(nodes_to_create)}
        , edges_to_create{std::move(edges_to_create)}
        , doubleEdges_to_create{std::move(doubleEdges_to_create)}
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
        , label{std::move(label)}
    {
    }

    void execute() const override;
};
