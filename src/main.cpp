﻿#include <iostream>
#include "drawer/drawer_commands/drawer_command_factory.h"
#include "drawer/graph_drawer_engine.h"
#include "other/algorithm.h"

int main(int argc, char** argv)
{
    // Создание фабрики по изготовлению команд для отрисовки
    auto& factory = drawerCommandFactory::get_instance();
    // Создание движка 
    auto& engine = graphDrawerEngine::get_instance();
    // Создание окна рендера
    auto& renderer = graphDrawer::get_instance();
    engine.set_graph_drawer(renderer);
    factory.set_engine(&engine);
    renderer.create_window();


    // Инициализация графа
    constexpr int count = 7;
    auto g = new graph(&engine, &factory, count);
    g->add_edge_flow(0, 1, 0, 3);
    g->add_edge_flow(1, 2, 0, 4);
    g->add_edge_flow(0, 2, 0, 3);
    g->add_edge_flow(2, 3, 0, 1);
    g->add_edge_flow(2, 4, 0, 2);
    g->add_edge_flow(3, 4, 0, 2);
    g->add_edge_flow(3, 5, 0, 6);
    g->add_edge_flow(1, 4, 0, 1);
    g->add_edge_flow(4, 6, 0, 1);
    g->add_edge_flow(5, 6, 0, 9);
    g->set_start(0);
    g->set_end(count - 1);

    g->maximize_flow();
    system("PAUSE");
    return 0;
}
