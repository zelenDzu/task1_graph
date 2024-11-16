#pragma once
#include "edge_type.h"
#include "edge_data.h"

class node;

class edge
{
public:
    const edgeType type;
    node* from = nullptr;
    node* to = nullptr;
    edgeData* data = nullptr;

    edge() = delete;

    edge(node* from, node* to, const edgeType type, edgeData* data)
        : type{type}
        , from{from}
        , to{to}
        , data{data}
    {
    }

    ~edge() { delete data; }
};
