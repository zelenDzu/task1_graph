#pragma once
#include <vector>
#include <graph/edge.h>

class node
{
public:
    unsigned int engine_id;

    unsigned int id;
    std::vector<edge*> edges;

    node() = default;

    node(const unsigned int id)
        : id{id}
    {}
};
