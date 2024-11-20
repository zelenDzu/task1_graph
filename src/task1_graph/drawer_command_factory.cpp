#include "drawer/drawer_commands/drawer_command_factory.h"

#define ERROR_CODE 1

const drawerCreateGraphCommand*
drawerCommandFactory::get_basic_graph_create_command(
    const graph* graph) const
{
    if (engine == nullptr)
        throw ERROR_CODE;

    constexpr float radius = 35.0f;

    std::vector<nodeShape*> nodes;
    std::vector<edgeShape*> edges;
    std::vector<doubleEdgeShape*> double_edges;
    const unsigned int size = graph->nodes.size();

    // First node
    std::string first_node_label(1, alphabet[0]);
    nodes.push_back(new nodeShape(
        std::move(first_node_label),
        point2D(X_CENTER - WIDTH(size) - OFFSET, Y_CENTER),
        DEFAULT,
        radius));

    // Other nodes
    for (int i = 1; i <= COUNT(size); i++)
    {
        const point2D point{
            X_CENTER + WIDTH(size) * std::cos(
                static_cast<float>(i) * THETA(size)),
            Y_CENTER + HEIGHT(size) * std::sin(
                static_cast<float>(i) * THETA(size))
        };

        std::string i_node_label(1, alphabet[i]);
        nodes.push_back(new nodeShape(
            std::move(i_node_label),
            point,
            DEFAULT,
            radius));
    }
    float xStart = X_CENTER - WIDTH(size) - OFFSET;
    float yStart = Y_CENTER;
    float xEnd = X_CENTER + WIDTH(size) * std::cos(
        static_cast<float>(4) * THETA(size));
    float yEnd = Y_CENTER + HEIGHT(size) * std::sin(
        static_cast<float>(4) * THETA(size));

    float angle = PI / 2 - std::atan((yEnd - yStart) / (xEnd - xStart));
    bool left_orientation = xEnd > xStart;
    float cos_offset = radius * std::cos(angle);
    float sin_offset = radius * std::sin(angle);

    edges.push_back(new edgeShape(graph->start->edges[0]->data->to_label(),
                                  point2D(
                                      get_offset_x(
                                          left_orientation,
                                          xStart,
                                          sin_offset),
                                      get_offset_x(
                                          left_orientation,
                                          yStart,
                                          cos_offset)),
                                  point2D{
                                      get_offset_y(
                                          left_orientation,
                                          xEnd,
                                          sin_offset),
                                      get_offset_y(
                                          left_orientation,
                                          yEnd,
                                          cos_offset)
                                  },
                                  DEFAULT,
                                  4.0f));

    // double_edges.push_back(new doubleEdgeShape("",
    //                               point2D(
    //                                   get_offset_x(
    //                                       left_orientation,
    //                                       xStart,
    //                                       sin_offset),
    //                                   get_offset_x(
    //                                       left_orientation,
    //                                       yStart,
    //                                       cos_offset)),
    //                               point2D{
    //                                   get_offset_y(
    //                                       left_orientation,
    //                                       xEnd,
    //                                       sin_offset),
    //                                   get_offset_y(
    //                                       left_orientation,
    //                                       yEnd,
    //                                       cos_offset)
    //                               },
    //                               DEFAULT,
    //                               4.0f, "2/0", "3/0"));

    // Last node
    std::string last_node_label(1, alphabet[COUNT(size) + 1]);
    nodes.push_back(new nodeShape(
        std::move(last_node_label),
        point2D(X_CENTER + WIDTH(size) + OFFSET, Y_CENTER),
        DEFAULT,
        radius));


    // тут будет return некой команды drawer_graph_create_command,
    // которая принимает std::vector<nodeShape>&& (ноды)
    // и std::vector<edgeShape>&& (рёбра)
    // и std::vector<doubleEdgeShape>&& (двойные рёбра)
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

    // TODO: Необходимо знать ID шейпа для заданного edge.
    // Об этом должен знать engine через таблицу маппинга, edge не должен знать
    return new drawerUpdateLabelCommand(engine,
                                        0u,//id
                                        edge.data->to_label());
}

const drawerCreateNodeCommand*
drawerCommandFactory::get_node_create_command(
    const node* graph) const
{
    if (engine == nullptr)
        throw ERROR_CODE;
    const auto nod = new nodeShape("A",
                                   {400.0f, 400.0f},
                                   DEFAULT,
                                   50.0f);
    return new drawerCreateNodeCommand(engine, *nod);
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
