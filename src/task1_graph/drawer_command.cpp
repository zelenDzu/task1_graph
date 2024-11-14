#include "drawer/drawer_commands/drawer_command.h"
#include "drawer/graph_drawer_engine.h"

void drawerCreateCommand::execute() const
{
    engine->add_shape(&shape_to_create);
}

void drawerDeleteCommand::execute() const
{

}

void drawerRecolorCommand::execute() const
{

}
