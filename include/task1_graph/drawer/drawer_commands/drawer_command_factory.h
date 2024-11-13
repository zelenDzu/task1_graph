#pragma once
#include "drawer_command.h"
#include "shape.h"
#include "graph.h"
#include "algorithm.h"
#include <cmath>

#define PI 3.141592f
#define COUNT(n) (n - 2)
#define DEG2RAD(n) ((n * PI) / 180)
#define RAD2DEG(n) ((n * 180) / PI)
#define X_CENTER 300.0f
#define Y_CENTER 300.0f
#define OFFSET 30.0f
#define BASE_WIDTH 100.0f
#define BASE_HEIGHT 50.0f
#define SCALE_WIDTH 10.0f
#define SCALE_HEIGHT 5.0f
#define WIDTH(x) (BASE_WIDTH + SCALE_WIDTH * COUNT(x))
#define HEIGHT(x) (BASE_HEIGHT + SCALE_HEIGHT * COUNT(x))
#define THETA(x) (2 * PI / COUNT(x))

class drawerCommandFactory
{
    graphDrawerEngine* engine;

    drawerCommandFactory() = default;

    ~drawerCommandFactory() = default;

public:
    static drawerCommandFactory& get_instance()
    {
        static drawerCommandFactory INSTANCE;
        return INSTANCE;
    }

    void set_engine(graphDrawerEngine* engine)
    {
        this->engine = engine;
    }

    const drawerCreateCommand* get_graph_create_command(
        const graph* graph) const
    {
        if (engine == nullptr)
            throw 1;

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

    // отрисовка графа обычного
    // орисовка графа остаточного
    // обновить ребра у графа обычного (лэйблы)
    // покрасить в цвет у графа обычного (default/red)
    // обновить остаточный граф (все ребра и их лэйблы)
    // покрасить в цвет у графа остаточного (default/red)
    // удалить граф остаточный
    // удалить граф обычный

    const drawerCreateCommand* get_node_create_command(const node* node) const
    {
        if (engine == nullptr)
            throw 1;

        // create 2d objects from 2d_space and supply command with these shapes
        return nullptr; // new drawerCreateCommand(engine, nullptr);
    }
};
