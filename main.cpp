#include <iostream>
using namespace std;

//#include "graph_drawer_engine.h"
//#include "drawer_command_factory.h"
#include "graph.h"

int main()
{
    int count = 7;
    graph* g = new graph(count);
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

    g->maximize_flow();

}

/*
int main2()
{
    // Сначала создаём рисовальщик. Он отвечает за связь с графической либой и примитивное рисование
    graphDrawer& drawer = graphDrawer::get_instance();

    // Затем создаём движок. Он управляет жизненным циклов всех графических сущностей - шейпов
    graphDrawerEngine& engine = graphDrawerEngine::get_instance();

    // Биндим рисовальщик к движку
    engine.set_graph_drawer(drawer);

    // Создаём фабрику, которая будет создавать наши команды движку рисования
    drawerCommandFactory& factory = drawerCommandFactory::get_instance();

    // Указываем фабрике какой движок используется
    factory.set_engine(&engine);


    // Например, на этом шаге нарисуем ровно три новых нода
    // вот у нас три нода каких-то
    node* node1 = new node(1);
    node* node2 = new node(2);
    node* node3 = new node(3);
    // Сделаем рёбра обоих типов
    edge* n1_to_n2 = new edge(node1, node2, edgeType::DIRECTIONAL, new edgeDataSingle(15));
    node1->edges.push_back(n1_to_n2);
    node2->edges.push_back(n1_to_n2);

    edge* n2_to_n3 = new edge(node2, node3, edgeType::BIDIRECTIONAL, new edgeDataFlow(3, 15));
    node2->edges.push_back(n2_to_n3);
    node3->edges.push_back(n2_to_n3);
    // Соберём из них граф
    graph* my_graph = new graph(node1, node3);
    my_graph->nodes.push_back(node2);

    // А дальше полёт фантазии
    // Методы из factory могут принимать что угодно из логических вариантов - ноды, эджи, сам граф и т.п.
    // Они:
    //     строят из элементов логики шейпы, которые будут рисоваться, и эти шейпы укладываются в команды на создание шейпов движком
    //     могут заказывать команды на обновление текущих шейпов (например, сменить цвет, или сменить label)
    //     могут заказывать команды на удаление шейпов из движка

     // Теперь можем выполнять логику самой программы...

    // Пример первичного рисования только трёх нодов
    engine
        .with_commands(
            factory.get_node_create_command(node1),
            factory.get_node_create_command(node2),
            factory.get_node_create_command(node3))
        ->step();

    // Желательно в factory сделать методы для создания команд на:
    //      Отрисовку целиком нового графа 
    //      Изменение цвета на подграфе-пути через последовательность вершин
    //      Изменение лейблов у эджей

    // А также нужно добавить классы команд под разные случаи шейпов.
    //      create_edge_shape_command - приказывает рисовать новую дугу
    //      create_node_shape_command - приказывает рисовать новый нод
    //      reset_edge_label_command - приказывает сменить лейбл у дуги по её id
    // и т.д.
}
*/