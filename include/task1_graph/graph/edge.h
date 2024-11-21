#pragma once
#include "edge_data.h"

class node;

enum edgeType
{
    DIRECTIONAL,
    BIDIRECTIONAL,
};

class edge
{
public:
    unsigned int engine_id;

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

    edge* get_backward() const;
};
