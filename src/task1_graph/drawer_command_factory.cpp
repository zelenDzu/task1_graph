#include "drawer/drawer_commands/drawer_command_factory.h"

#define ERROR_CODE 1

const drawerCreateGraphCommand*
drawerCommandFactory::get_basic_graph_create_command(
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

const drawerUpdateLabelCommand*
drawerCommandFactory::get_update_edge_flow_label_command(
    const edge& edge) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    // TODO: Необходимо знать ID шейпа для заданного edge.
    // Об этом должен знать engine через таблицу маппинга, edge не должен знать
    return new drawerUpdateLabelCommand(engine,
                                        0u,
                                        edge.data->to_label());
}

const drawerRecolorCommand*
drawerCommandFactory::get_recolor_edge_to_red_command(
    const edge& edge) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    // TODO: Необходимо знать ID шейпа для заданного edge
    return new drawerRecolorCommand(engine, 0u, true);
}

const drawerRecolorCommand*
drawerCommandFactory::get_recolor_edge_to_default_command(
    const edge& edge) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    // TODO: Необходимо знать ID шейпа для заданного edge
    return new drawerRecolorCommand(engine, 0u, false);
}

const drawerDeleteCommand* drawerCommandFactory::get_graph_delete_command(
    const graph* graph) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    // TODO: Необходимо получить все ID шейпов, которые относятся к графу
    // И положить их в vector, который отдать в аргумент конструктору ниже
    return new drawerDeleteCommand(engine, {0u, 1u, 2u});
}
