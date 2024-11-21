#pragma once
#include "node.h"
#include "other/algorithm.h"


class graphDrawerEngine;
class drawerCommandFactory;

enum graph_type
{
    FLOW,
    RESIDUAL
};

class graph
{
public:
    node* start = nullptr;
    node* end = nullptr;
    graph_type type = FLOW;
    std::vector<node*> nodes;
    graphDrawerEngine* engine = nullptr;
    drawerCommandFactory* factory = nullptr;

    graph() = delete;

    graph(graphDrawerEngine* engine,
          drawerCommandFactory* factory,
          unsigned int nodes_count);

    graph(graphDrawerEngine* engine,
          drawerCommandFactory* factory,
          unsigned int nodes_count,
          graph_type type);

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

    void show_data() const;

    void update_residual_network(graph* res_net);

    stack* find_shortest_path(unsigned int from,
                              unsigned int to) const;

    stack* find_shortest_path() const;

    edge* get_edge(unsigned int from, unsigned int to) const;

    void apply_augmenting_path(const stack* path, const graph* res_net);

    void maximize_flow();

    void update_flow_edge(edge* orig_edge);

    std::vector<node*> get_all_nodes() const;

    std::vector<edge*> get_all_edges() const;
};
