#pragma once
#include "drawer_command.h"
#include "graph/graph.h"
#include "other/algorithm.h"
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
        const graph* graph) const;

    // отрисовка графа обычного
    // орисовка графа остаточного
    // обновить ребра у графа обычного (лэйблы)
    // покрасить в цвет у графа обычного (default/red)
    // обновить остаточный граф (все ребра и их лэйблы)
    // покрасить в цвет у графа остаточного (default/red)
    // удалить граф остаточный
    // удалить граф обычный
};
