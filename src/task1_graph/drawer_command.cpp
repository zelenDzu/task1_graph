#include "drawer/drawer_commands/drawer_command.h"
#include "drawer/graph_drawer_engine.h"

void drawerCreateNodeCommand::execute() const
{
    auto& drawer = engine->get_graph_drawer();
    shape_to_create.circle_id =
        drawer.draw_circle(shape_to_create.radius,
                           shape_to_create.initial_point.x,
                           shape_to_create.initial_point.y);
    const point2D label_point = shape_to_create.get_label_point();
    shape_to_create.label_id =
        drawer.draw_label(shape_to_create.label,
                          label_point.x,
                          label_point.y);
    shape_to_create.shape_id = engine->add_shape(&shape_to_create);
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
    graphDrawer& drawer = engine->get_graph_drawer();
    drawer.recolor_shape(shape_id,
                         mark ? drawer.RED : drawer.YELLOW);
}

void drawerCreateGraphCommand::execute() const
{
    // TODO: Check color consistency on create
    graphDrawer& drawer = engine->get_graph_drawer();
    for (const auto& [nod_shape, nod] : nodes_to_create)
    {
        nod_shape->circle_id =
            drawer.draw_circle(nod_shape->radius,
                               nod_shape->initial_point.x,
                               nod_shape->initial_point.y);
        const point2D label_point = nod_shape->get_label_point();
        nod_shape->label_id =
            drawer.draw_label(nod_shape->label,
                              label_point.x,
                              label_point.y);
        nod_shape->shape_id = engine->add_shape(nod_shape);
        nod->engine_id = nod_shape->shape_id;
    }
    for (const auto& [edge_shape, edge] : edges_to_create)
    {
        edge_shape->arrow_id =
            drawer.draw_arrow(edge_shape->initial_point.x,
                              edge_shape->initial_point.y,
                              edge_shape->end_point.x,
                              edge_shape->end_point.y,
                              edge_shape->width);
        const point2D label_point = edge_shape->get_label_point();
        edge_shape->label_id =
            drawer.draw_label(edge_shape->label,
                              label_point.x,
                              label_point.y);
        edge_shape->shape_id = engine->add_shape(edge_shape);
        edge->engine_id = edge_shape->shape_id;
    }
    for (const auto& [edge_shape, edge] : doubleEdges_to_create)
    {
        edge_shape->forward.arrow_id =
            drawer.draw_arrow(edge_shape->forward.initial_point.x,
                              edge_shape->forward.initial_point.y,
                              edge_shape->forward.end_point.x,
                              edge_shape->forward.end_point.y,
                              edge_shape->width);
        edge_shape->backward.arrow_id =
            drawer.draw_arrow(edge_shape->backward.initial_point.x,
                              edge_shape->backward.initial_point.y,
                              edge_shape->backward.end_point.x,
                              edge_shape->backward.end_point.y,
                              edge_shape->width);
        const point2D label_point = edge_shape->get_label_point();
        const point2D forward_label_point = edge_shape->forward.
            get_label_point();
        const point2D backward_label_point = edge_shape->backward.
            get_label_point();
        edge_shape->label_id =
            drawer.draw_label(edge_shape->label,
                              label_point.x,
                              label_point.y);
        edge_shape->forward.label_id =
            drawer.draw_label(edge_shape->forward.label,
                              forward_label_point.x,
                              forward_label_point.y);
        edge_shape->backward.label_id =
            drawer.draw_label(edge_shape->backward.label,
                              backward_label_point.x,
                              backward_label_point.y);
        edge_shape->shape_id = engine->add_shape(edge_shape);
        edge->engine_id = edge_shape->shape_id;
    }
}

void drawerUpdateLabelCommand::execute() const
{
    engine->get_graph_drawer()
          .rename_label(engine->get_shape_label_id(shape_id),
                        label);
}
