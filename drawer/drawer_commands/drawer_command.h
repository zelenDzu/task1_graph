#pragma once
#include "shape.h"
#include "graph_drawer_engine.h"

/**
 * Команда, которая выполняется на движке
 */
struct drawerCommand
{
    graphDrawerEngine* engine;

    drawerCommand() = delete;

    drawerCommand(graphDrawerEngine* engine) : engine{engine} {}

    ~drawerCommand() = default;

    virtual void execute() const = 0;
};