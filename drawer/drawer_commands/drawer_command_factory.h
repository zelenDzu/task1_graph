#pragma once
#include "drawer_create_command.h"
#include "drawer_delete_command.h"
#include "drawer_recolor_command.h"
#include "graph.h"
#include "node_shape.h"

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

    const drawerCreateCommand* get_graph_create_command(const graph* graph) const
    {

    }

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