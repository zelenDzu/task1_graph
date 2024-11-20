#include "graph/graph.h"

graph::graph(const unsigned int nodes_count)
{
    for (unsigned int i = 0u; i < nodes_count; i++)
    {
        nodes.push_back(new node(i));
    }
    start = nodes.front();
    end = nodes.back();
}

graph::graph(const unsigned int nodes_count, const graph_type type) : graph(nodes_count)
{
    this->type = type;
}

void graph::add_node()
{
    const unsigned int id = nodes.size();
    nodes.push_back(new node(id));
}

void graph::set_start(const unsigned int id)
{
    if (id < nodes.size())
        start = nodes[id];
}

void graph::set_end(const unsigned int id)
{
    if (id < nodes.size())
        end = nodes[id];
}

void graph::add_edge_single(const unsigned int start_id,
                            const unsigned int end_id,
                            const int value,
                            const edgeType type)
{
    if (start_id < nodes.size() && end_id < nodes.size())
    {
        node* from = nodes[start_id];
        node* to = nodes[end_id];
        edge* new_edge = new
            edge(from, to, type, new edgeDataSingle(value));
        from->edges.push_back(new_edge);
    }
}

void graph::add_edge_flow(const unsigned int start_id,
                          const unsigned int end_id,
                          const int flow,
                          const int capacity,
                          const edgeType type)
{
    if (start_id < nodes.size() && end_id < nodes.size())
    {
        node* from = nodes[start_id];
        node* to = nodes[end_id];
        edge* new_edge = new edge(from,
                                  to,
                                  type,
                                  new edgeDataFlow(capacity, flow));
        from->edges.push_back(new_edge);
    }
}

void graph::clear_edges()
{
    for (node* nod : nodes)
    {
        nod->edges.clear();
    }
}

void graph::show() const
{
    std::cout << "\n\nNodes count: " << nodes.size();
    for (const node* v : nodes)
    {
        std::cout << "\nNode " << alphabet[v->id];
        for (const edge* e : v->edges)
        {
            if (type == RESIDUAL)
            {
                // TODO: dynamic_cast usage here - ошибка проектирования
                const int value =
                    dynamic_cast<edgeDataSingle*>(e->data)->value;
                std::cout << "\n\t" << alphabet[e->to->id] << ": " << value;
            }
            else
            {
                // TODO: dynamic_cast usage here - ошибка проектирования
                const edgeDataFlow* edge_data =
                    dynamic_cast<edgeDataFlow*>(e->data);
                const int flow = edge_data->flow;
                const int capacity = edge_data->capacity;
                std::cout
                    << "\n\t"
                    << alphabet[e->to->id] << ": " << flow << "/" << capacity;
            }
        }
    }
}

void graph::update_residual_network(graph* res_net)
{
    res_net->clear_edges();
    for (const node* v : nodes)
    {
        for (const edge* e : v->edges)
        {
            // TODO: dynamic_cast usage here - ошибка проектирования
            const edgeDataFlow* edge_data =
                dynamic_cast<edgeDataFlow*>(e->data);
            const int capacity = edge_data->capacity;
            const int flow = edge_data->flow;
            edgeType type;

            if (capacity - flow > 0 && flow > 0)
                type = BIDIRECTIONAL;
            else
                type = DIRECTIONAL;

            if (capacity - flow > 0)
            {
                res_net->add_edge_single(e->from->id,
                                         e->to->id,
                                         capacity - flow,
                                         type);
            }

            if (flow > 0)
            {
                res_net->add_edge_single(e->to->id,
                                         e->from->id,
                                         flow,
                                         type);
            }
        }
    }
}

stack* graph::find_shortest_path(const unsigned int from,
                                 const unsigned int to) const
{
    node* n_from = nodes[from];
    node* n_to = nodes[to];
    stack* path = new stack(); // final answer
    queue* q = new queue(); // queue of nodes to check
    std::vector<int> explored = std::vector<int>(nodes.size());
    // 0 if node not explored, 1 otherwise
    // TODO: Проверить на уместность unsigned int вместо int
    q->enqueue(from, nullptr);
    explored[from] = 1;
    while (!q->is_empty())
    {
        s_node* v = q->dequeue(); // current node to check
        if (v->val == to)
        {
            do
            {
                path->push(v->val);
                v = v->parent;
            }
            while (v != nullptr);

            delete q;
            break;
        }

        bool has_children = false;
        for (const edge* e : nodes[v->val]->edges)
        {
            int w_id = e->to->id;
            if (!explored[w_id])
            {
                has_children = true;
                explored[w_id] = 1;
                q->enqueue(w_id, v);
            }
        }
        if (!has_children) delete v;
    }
    return path;
}

stack* graph::find_shortest_path() const
{
    return find_shortest_path(start->id, end->id);
}

edge* graph::get_edge(const unsigned int from, const unsigned int to) const
{
    int k = 0;
    edge* e = nullptr;
    while (k < nodes[from]->edges.size())
    {
        e = nodes[from]->edges[k];
        k++;
        if (e->to->id == to) break;
    }
    return e && e->to->id == to ? e : nullptr;
}

void graph::apply_augmenting_path(const stack* path, const graph* res_net)
{
    if (!path->top) return;

    const s_node* v = path->top;
    int min_val = INT_MAX;

    while (v->next)
    {
        const int from = v->val;
        const int to = v->next->val;
        const edge* e = res_net->get_edge(from, to);
        if (const int value = dynamic_cast<edgeDataSingle*>(e->data)->value;
            value < min_val)
        {
            min_val = value;
        }
        v = v->next;
    }

    v = path->top;
    while (v->next)
    {
        const int from = v->val;
        const int to = v->next->val;
        // TODO: unsigned int здесь будет корректен? Если это ID, то да
        if (const edge* orig_edge = get_edge(from, to))
        {
            dynamic_cast<edgeDataFlow*>(orig_edge->data)->flow += min_val;
        }
        else
        {
            orig_edge = get_edge(to, from);
            dynamic_cast<edgeDataFlow*>(orig_edge->data)->flow -= min_val;
        }
        v = v->next;
    }
}

void graph::maximize_flow()
{
    graph* res_net = new graph(nodes.size(), RESIDUAL);
    res_net->start = res_net->nodes[start->id];
    res_net->end = res_net->nodes[end->id];
    stack* path = new stack();
    do
    {
        apply_augmenting_path(path, res_net);
        update_residual_network(res_net);
        path = res_net->find_shortest_path();
    }
    while (!path->is_empty());

    delete res_net;
    delete path;
}
