#pragma once
#include <vector>
#include <edge.h>

class node
{
public:
    unsigned int id;
    std::vector<edge*> edges;

    node() = default;

    node(const unsigned int id)
        : id{id}
    {
    }
};
