#pragma once
#include "drawer_command.h"
#include "graph/graph.h"
#include "other/algorithm.h"
#include <cmath>

#define PI 3.141592f
#define COUNT(n) (n - 2)
#define DEG2RAD(n) ((n * PI) / 180)
#define RAD2DEG(n) ((n * 180) / PI)
#define X_CENTER 620.0f
#define Y_CENTER 620.0f
#define OFFSET 90.0f
#define BASE_WIDTH 100.0f
#define BASE_HEIGHT 100.0f
#define SCALE_WIDTH 20.0f
#define SCALE_HEIGHT 20.0f
#define WIDTH(x) (BASE_WIDTH + SCALE_WIDTH * COUNT(x))
#define HEIGHT(x) (BASE_HEIGHT + SCALE_HEIGHT * COUNT(x))
#define THETA(x) (2 * PI / COUNT(x))

class drawerCommandFactory
{
    static constexpr float BASIC_EDGE_WIDTH = 4.0f;
    static constexpr float BASIC_NODE_RADIUS = 35.0f;

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

    /**
     * Изготовление команды на отрисовку обычного графа
     * @param graph Логический граф на отрисовку
     * @return Команда на отрисовку графа
     */
    const drawerCreateGraphCommand* get_basic_graph_create_command(
        const graph* graph) const;

    /**
     * Изготовление команды на отрисовку остаточного графа
     * @param graph Логический граф на отрисовку
     * @return Команда на отрисовку графа
     */
    const drawerCreateGraphCommand* get_remained_graph_create_command(
        const graph* graph) const;

    /**
     * Изготовление команды на обновления лейбла ребра
     * @param edge Ребро для обновления
     * @return Команда на обновление лейбла
     */
    const drawerUpdateLabelCommand* get_update_edge_flow_label_command(
        const edge& edge) const;

    /**
     * Изготовление команды на перекрашивание edge в красный цвет
     * @param edge Ребро для обновления
     * @return Команда на перекраску
     */
    const drawerRecolorCommand* get_recolor_edge_to_red_command(
        const edge& edge) const;

    /**
     * Изготовление команды на перекрашивание edge в дефолтный цвет
     * @param edge Ребро для обновления
     * @return Команда на перекраску
     */
    const drawerRecolorCommand* get_recolor_edge_to_default_command(
        const edge& edge) const;
};
