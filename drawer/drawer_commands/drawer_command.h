#pragma once
#include "shape.h"

class graphDrawerEngine;
/**
 * Команда, которая выполняется на движке
 */
struct drawerCommand
{
    graphDrawerEngine* engine;

    drawerCommand() = delete;

    drawerCommand(graphDrawerEngine* engine) : engine{engine} {}

    virtual ~drawerCommand() = default;

    virtual void execute() const = 0;
};