#pragma once
#include "drawer_command.h"
#include "graph/graph.h"
#include "other/algorithm.h"
#include <cmath>

#define COUNT(n) (n - 2) // количество точек (без первой и последней)
#define DEG2RAD(n) ((n * PI) / 180) // градусы в радианы
#define RAD2DEG(n) ((n * 180) / PI) // радианы в градусы
#define X_CENTER 620.0f // абсцисса центра графа
#define Y_CENTER(offset) (1020.0f - offset) // ордината центра графа
#define OFFSET 150.0f // сдвиг для первой и последней точки
#define BASE_WIDTH 80.0f // базовая ширина графа
#define BASE_HEIGHT 100.0f // базовая высота графа
#define SCALE_WIDTH 30.0f // коэффициент увеличения ширины графа
#define SCALE_HEIGHT 20.0f // коэффициент увеличения высоты графа
#define WIDTH(x) (BASE_WIDTH + SCALE_WIDTH * COUNT(x)) // ширина графа
#define HEIGHT(x) (BASE_HEIGHT + SCALE_HEIGHT * COUNT(x)) // высота графа
#define THETA(x) (2 * PI / COUNT(x)) // угол расстояния между вершинами

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
     * Изготовление команды на удаление шейпа
     * @param graph Логический граф на удаление
     * @return Команда на удаление
     */
    const drawerDeleteCommand* get_graph_delete_command(
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
    const drawerEdgeRecolorCommand* get_recolor_edge_to_red_command(
        const edge& edge) const;

    /**
     * Изготовление команды на перекрашивание edge в дефолтный цвет
     * @param edge Ребро для обновления
     * @return Команда на перекраску
     */
    const drawerEdgeRecolorCommand* get_recolor_edge_to_default_command(
        const edge& edge) const;
};
