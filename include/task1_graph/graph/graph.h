#pragma once
#include "node.h"
#include "other/algorithm.h"

class graph
{
public:
    node* start = nullptr;
    node* end = nullptr;
    std::vector<node*> nodes;

    graph() = default;

    //graph(node* start, node* end) : start{start}, end{end} {}

    graph(unsigned int nodes_count);

    void add_node();

    void set_start(unsigned int id);

    void set_end(unsigned int id);

    void add_edge_single(unsigned int start_id,
                         unsigned int end_id,
                         int value,
                         edgeType type = DIRECTIONAL);

    void add_edge_flow(unsigned int start_id,
                       unsigned int end_id,
                       int flow,
                       int capacity,
                       edgeType type = DIRECTIONAL);

    void clear_edges();

    void show(bool res) const;

    void update_residual_network(graph* res_net);

    stack* find_shortest_path(unsigned int from,
                              unsigned int to) const;

    stack* find_shortest_path() const;

    edge* get_edge(unsigned int from, unsigned int to) const;

    void apply_augmenting_path(const stack* path, const graph* res_net);

    void maximize_flow();
};
