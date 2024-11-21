#include "drawer/drawer_commands/drawer_command_factory.h"

#include <map>

#include "drawer/graph_drawer_engine.h"

#define ERROR_CODE 1

const drawerCreateGraphCommand*
drawerCommandFactory::get_basic_graph_create_command(
    const graph* graph) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    const float offset = graph->type == RESIDUAL ? 500 : 0;

    std::map<nodeShape*, node*> nodes;
    std::map<node*, nodeShape*> nodes_reverse;
    std::map<edgeShape*, edge*> edges;
    std::map<doubleEdgeShape*, edge*> double_edges;

    // Сортированные списки уникальных нод и ребер
    const std::vector<node*> graph_nodes{std::move(graph->get_all_nodes())};
    const std::vector<edge*> graph_edges{std::move(graph->get_all_edges())};

    const unsigned int size = graph_nodes.size();

    // Первая нода
    std::string first_node_label(1, alphabet[0]);
    const auto first_node = new nodeShape(
        std::move(first_node_label),
        point2D(X_CENTER - WIDTH(size) - OFFSET, Y_CENTER(offset)),
        DEFAULT,
        BASIC_NODE_RADIUS);
    nodes[first_node] = graph_nodes[0];
    nodes_reverse[graph_nodes[0]] = first_node;

    // Срединные ноды
    for (unsigned int i = 1u; i < size - 1u; i++)
    {
        const point2D point{
            X_CENTER + WIDTH(size) * std::cos(
                static_cast<float>(i) * THETA(size)),
            Y_CENTER(offset) + HEIGHT(size) * std::sin(
                static_cast<float>(i) * THETA(size))
        };

        std::string i_node_label(1, alphabet[i]);
        const auto i_node = new nodeShape(
            std::move(i_node_label),
            point,
            DEFAULT,
            BASIC_NODE_RADIUS);
        nodes[i_node] = graph_nodes[i];
        nodes_reverse[graph_nodes[i]] = i_node;
    }

    // Последняя нода
    std::string last_node_label(1, alphabet[size - 1]);
    const auto last_node = new nodeShape(
        std::move(last_node_label),
        point2D(X_CENTER + WIDTH(size) + OFFSET, Y_CENTER(offset)),
        DEFAULT,
        BASIC_NODE_RADIUS);
    nodes[last_node] = graph_nodes[size - 1];
    nodes_reverse[graph_nodes[size - 1]] = last_node;

    // Ребра
    for (unsigned int i = 0u; i < graph_edges.size(); i++)
    {
        const auto current_edge = graph_edges[i];
        const auto start_node_shape = nodes_reverse[current_edge->from];
        const auto end_node_shape = nodes_reverse[current_edge->to];

        const bool left_orientation =
            end_node_shape->initial_point.x > start_node_shape->initial_point.x;
        const float angle = PI / 2 - atan(
            (end_node_shape->initial_point.y -
                start_node_shape->initial_point.y) /
            (end_node_shape->initial_point.x -
                start_node_shape->initial_point.x));
        const float cos = std::cos(angle);
        const float sin = std::sin(angle);
        const float cos_offset = BASIC_NODE_RADIUS * cos;
        const float sin_offset = BASIC_NODE_RADIUS * sin;
        const point2D start_shifted_point{
            get_offset_x(
                left_orientation,
                start_node_shape->initial_point.x,
                sin_offset),
            get_offset_x(
                left_orientation,
                start_node_shape->initial_point.y,
                cos_offset)
        };
        const point2D end_shifted_point{
            get_offset_y(
                left_orientation,
                end_node_shape->initial_point.x,
                sin_offset),
            get_offset_y(
                left_orientation,
                end_node_shape->initial_point.y,
                cos_offset)
        };

        if (current_edge->type == DIRECTIONAL)
        {
            const auto edge = new edgeShape(
                graph_edges[i]->data->to_label(),
                start_shifted_point,
                end_shifted_point,
                DEFAULT,
                BASIC_EDGE_WIDTH);
            edges[edge] = current_edge;
        }
        else if (current_edge->type == BIDIRECTIONAL)
        {
            const auto double_edge = new doubleEdgeShape(
                "",
                start_shifted_point,
                end_shifted_point,
                DEFAULT,
                BASIC_EDGE_WIDTH,
                std::move(current_edge->data->to_label()),
                std::move(current_edge->get_backward()->data->to_label()));
            double_edges[double_edge] = current_edge;
        }
    }

    return new drawerCreateGraphCommand(engine,
                                        std::move(nodes),
                                        std::move(edges),
                                        std::move(double_edges));
}

const drawerUpdateLabelCommand*
drawerCommandFactory::get_update_edge_flow_label_command(
    const edge& edge) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    return new drawerUpdateLabelCommand(engine,
                                        edge.engine_id,
                                        edge.data->to_label());
}

const drawerEdgeRecolorCommand*
drawerCommandFactory::get_recolor_edge_to_red_command(
    const edge& edge) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    return new
        drawerEdgeRecolorCommand(engine, edge.engine_id, true, edge.type);
}

const drawerEdgeRecolorCommand*
drawerCommandFactory::get_recolor_edge_to_default_command(
    const edge& edge) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    return new
        drawerEdgeRecolorCommand(engine, edge.engine_id, false, edge.type);
}
