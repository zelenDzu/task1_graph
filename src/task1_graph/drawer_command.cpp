#include "drawer/drawer_commands/drawer_command.h"
#include "drawer/graph_drawer_engine.h"

void drawerCreateCommand::execute() const
{
    engine->add_shape(&shape_to_create);
}

void drawerDeleteCommand::execute() const
{
    for (const unsigned int id : shapes_id)
    {
        engine->get_graph_drawer().erase_drawing(id);
        engine->remove_shape(id);
    }
}

void drawerRecolorCommand::execute() const
{
    auto& drawer = engine->get_graph_drawer();
    drawer.recolor_shape(shape_id,
        mark ? drawer.RED : drawer.YELLOW);
    // TODO: Здесь выбирать цвета для покраски, можно и через тело команды
}

void drawerCreateGraphCommand::execute() const
{
    for (nodeShape* nod : nodes_to_create)
    {
        const unsigned int id =
            engine->get_graph_drawer().draw_circle(nod->radius,
                                               nod->initial_point.x,
                                               nod->initial_point.y);
        engine->add_shape(nod);
        // TODO: Сделать нормальную ID систему. add_shape(id, nod)
    }
    for (edgeShape* edge : edges_to_create)
    {
        const unsigned int id =
            engine->get_graph_drawer().draw_arrow(
                edge->initial_point.x,
                edge->initial_point.y,
                edge->end_point.x,
                edge->end_point.y,
                edge->width);
        engine->add_shape(edge);
    }
}

void drawerUpdateLabelCommand::execute() const
{
    engine->get_graph_drawer().rename_label(shape_id, label);
}
