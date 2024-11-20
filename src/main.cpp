#include <iostream>
#include "drawer/drawer_commands/drawer_command_factory.h"
#include "drawer/graph_drawer_engine.h"

int main(int argc, char** argv)
{
    auto& factory = drawerCommandFactory::get_instance();
    auto& engine = graphDrawerEngine::get_instance();
    auto& renderer = graphDrawer::get_instance();
    engine.set_graph_drawer(renderer);
    factory.set_engine(&engine);
    renderer.create_window();


    constexpr int count = 7;
    auto g = new graph(count);
    g->add_edge_flow(0, 1, 0, 3);
    g->add_edge_flow(0, 3, 0, 3);
    g->add_edge_flow(1, 2, 0, 4);
    g->add_edge_flow(2, 0, 0, 3);
    g->add_edge_flow(2, 3, 0, 1);
    g->add_edge_flow(2, 4, 0, 2);
    g->add_edge_flow(3, 4, 0, 2);
    g->add_edge_flow(3, 5, 0, 6);
    g->add_edge_flow(4, 1, 0, 1);
    g->add_edge_flow(4, 6, 0, 1);
    g->add_edge_flow(5, 6, 0, 9);
    g->set_start(0);
    g->set_end(count - 1);

    engine.with_commands({
            factory.get_basic_graph_create_command(g),
        }
    )->step();
    renderer.recolor_shape(13, sf::Color::Red);
    renderer.render();
    g->maximize_flow();
    return 0;
}
