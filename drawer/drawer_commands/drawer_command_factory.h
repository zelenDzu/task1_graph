#pragma once
#include "drawer_create_command.h"
#include "drawer_delete_command.h"
#include "drawer_recolor_command.h"
#include "graph.h"
#include "node_shape.h"
#include "algorithm.h"
//#include <iostream>
#include <cmath>

constexpr double pi = 3.14159265358979323846;

class drawerCommandFactory
{
private:
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

    //

    const drawerCreateCommand* get_graph_create_command(const graph* graph) const
    {
        if (engine == nullptr)
            throw - 1;

        std::vector<nodeShape*> nodes = std::vector<nodeShape*>();
        
        int n = graph->nodes.size() - 2;
        int x_center = 300;
        int y_center = 300;
        int offset = 30;
        int base_width = 100;
        int base_height = 50;
        double scale_w = 10;
        double scale_h = 5;
        double width = base_width + n * scale_w;
        double height = base_height + n * scale_h;
        double theta = 2 * pi / n;

        // first node
        nodes.push_back(new nodeShape(
            &alphabet[0],
            point2D(x_center - width - offset, y_center),
            0, 5));

        for (int i = 1; i <= n; i++)
        {
            nodes.push_back(new nodeShape(
                &alphabet[i],
                point2D(
                    x_center + width * cos(i * theta), 
                    y_center + height * sin(i * theta)),
                0, 5));
        }

        nodes.push_back(new nodeShape(
            &alphabet[n + 1],
            point2D(x_center + width + offset, y_center),
            0, 5));

        
        // тут будет return некой команды drawer_graph_create_command, 
        // которая принимает vector<2d_shape> (ноды и ребра)
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
        // TODO: Описать, как создаются шейпы для наших нодов. Связать логику (нод) и графику (шейп нода)
        // тут же и опредяляется логика того, какие будут КООРДИНАТЫ и всё такое
        
        // Движок нужен для того чтобы команда знала где исполняться
        if (engine == nullptr) 
            throw -1;
 
        // create 2d objects from 2d_space and supply command with these shapes
        return new drawerCreateCommand(engine, 
                                    // new nodeShape(...аргументы и факты); и переходишь к nodeShape, используешь соответствующий конструктор. А пока 
                                    nullptr
        );
    }
};