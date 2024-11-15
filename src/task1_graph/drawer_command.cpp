#include "drawer/drawer_commands/drawer_command.h"
#include "drawer/graph_drawer_engine.h"

void drawerCreateCommand::execute() const
{
    engine->add_shape(&shape_to_create);
}

void drawerDeleteCommand::execute() const
{
    for (const unsigned int shape_id : shapes_id)
    {
        std::vector<unsigned int> elements_to_erase{
            std::move(engine->get_shape(shape_id)->get_id_list())
        };

        for (const unsigned int element_id : elements_to_erase)
        {
            engine->get_graph_drawer().erase_drawing(element_id);
        }
        engine->remove_shape(shape_id);
    }
}

void drawerRecolorCommand::execute() const
{
    auto& drawer = engine->get_graph_drawer();
    drawer.recolor_shape(shape_id,
                         mark ? drawer.RED : drawer.YELLOW);
}

void drawerCreateGraphCommand::execute() const
{
    // TODO: Check color consistency on create
    auto& drawer = engine->get_graph_drawer();
    for (nodeShape* nod : nodes_to_create)
    {
        nod->circle_id =
            drawer.draw_circle(nod->radius,
                               nod->initial_point.x,
                               nod->initial_point.y);
        const point2D label_point = nod->get_label_point();
        nod->label_id =
            drawer.draw_label(nod->label,
                              label_point.x,
                              label_point.y);
        nod->shape_id = engine->add_shape(nod);
    }
    for (edgeShape* edge : edges_to_create)
    {
        edge->arrow_id =
            drawer.draw_arrow(edge->initial_point.x,
                              edge->initial_point.y,
                              edge->end_point.x,
                              edge->end_point.y,
                              edge->width);
        const point2D label_point = edge->get_label_point();
        edge->label_id =
            drawer.draw_label(edge->label,
                              label_point.x,
                              label_point.y);
        edge->shape_id = engine->add_shape(edge);
    }
    for (doubleEdgeShape* edge : doubleEdges_to_create)
    {
        edge->forward.arrow_id =
            drawer.draw_arrow(edge->forward.initial_point.x,
                              edge->forward.initial_point.y,
                              edge->forward.end_point.x,
                              edge->forward.end_point.y,
                              edge->width);
        edge->backward.arrow_id =
            drawer.draw_arrow(edge->backward.initial_point.x,
                              edge->backward.initial_point.y,
                              edge->backward.end_point.x,
                              edge->backward.end_point.y,
                              edge->width);
        const point2D label_point = edge->get_label_point();
        const point2D forward_label_point = edge->forward.get_label_point();
        const point2D backward_label_point = edge->backward.get_label_point();
        edge->label_id =
            drawer.draw_label(edge->label,
                              label_point.x,
                              label_point.y);
        edge->forward.label_id =
            drawer.draw_label(edge->forward.label,
                              forward_label_point.x,
                              forward_label_point.y);
        edge->backward.label_id =
            drawer.draw_label(edge->backward.label,
                              backward_label_point.x,
                              backward_label_point.y);
        edge->shape_id = engine->add_shape(edge);
    }
}

void drawerUpdateLabelCommand::execute() const
{
    engine->get_graph_drawer()
          .rename_label(engine->get_shape_label_id(shape_id),
                        label);
}
