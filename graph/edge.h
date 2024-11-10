#pragma once
#include "edge_type.h"
#include "edge_data.h"
#include "node.h"

class node;

class edge
{
    public:
        const edgeType type;
        node* from;
        node* to;
        edgeData* data;

        edge() = delete;

        edge(node* from, node* to, edgeType type, edgeData* data) : type{type}, from{from}, to{to}, data{data} {}

        // TODO: Обратить внимание, что при удалении edge могут затеряться ссылки на нод и быть утечка памяти
        ~edge() { delete data; }
};