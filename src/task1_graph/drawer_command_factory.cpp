#include "drawer/drawer_commands/drawer_command_factory.h"

#define ERROR_CODE 1

const drawerCreateCommand* drawerCommandFactory::get_graph_create_command(
    const graph* graph) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    std::vector<nodeShape*> nodes;
    const unsigned int size = graph->nodes.size();

    // First node
    nodes.push_back(new nodeShape(
        &alphabet[0],
        point2D(X_CENTER - WIDTH(size) - OFFSET, Y_CENTER),
        0,
        5));

    // Other nodes
    for (int i = 1; i <= COUNT(size); i++)
    {
        nodes.push_back(new nodeShape(
            &alphabet[i],
            point2D(
                X_CENTER + WIDTH(size) * std::cos(
                    static_cast<float>(i) * THETA(size)),
                Y_CENTER + HEIGHT(size) * std::sin(
                    static_cast<float>(i) * THETA(size))),
            0,
            5));
    }

    // Last node
    nodes.push_back(new nodeShape(
        &alphabet[COUNT(size) + 1],
        point2D(X_CENTER + WIDTH(size) + OFFSET, Y_CENTER),
        0,
        5));

    // тут будет return некой команды drawer_graph_create_command,
    // которая принимает std::vector<node_shape>& (ноды)
    // и std::vector<edge_shape>& (рёбра)
    return nullptr;
}
