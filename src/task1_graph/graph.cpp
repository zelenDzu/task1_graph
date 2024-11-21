#include "graph/graph.h"

#include <map>
#include <set>

#include "drawer/graph_drawer_engine.h"
#include "drawer/drawer_commands/drawer_command_factory.h"

graph::graph(graphDrawerEngine* engine,
             drawerCommandFactory* factory,
             const unsigned int nodes_count)
    : engine{engine}
    , factory{factory}
{
    for (unsigned int i = 0u; i < nodes_count; i++)
    {
        nodes.push_back(new node(i));
    }
    start = nodes.front();
    end = nodes.back();
}

graph::graph(graphDrawerEngine* engine,
             drawerCommandFactory* factory,
             const unsigned int nodes_count,
             const graph_type type)
    : graph(engine, factory, nodes_count)
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

void graph::show_data() const
{
    std::cout << "\n\nNodes count: " << nodes.size();
    for (const node* v : nodes)
    {
        std::cout << "\nNode " << alphabet[v->id];
        for (const edge* e : v->edges)
        {
            if (type == RESIDUAL)
            {
                const int value =
                    dynamic_cast<edgeDataSingle*>(e->data)->value;
                std::cout << "\n\t" << alphabet[e->to->id] << ": " << value;
            }
            else
            {
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
    engine->with_commands({
        factory->get_graph_delete_command(res_net)
        })->step();
    res_net->clear_edges();
    for (const node* v : nodes)
    {
        for (const edge* e : v->edges)
        {
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
    engine->with_commands({
        factory->get_basic_graph_create_command(res_net)
        })->step();
}

stack* graph::find_shortest_path(const unsigned int from,
                                 const unsigned int to) const
{
    node* n_from = nodes[from];
    node* n_to = nodes[to];
    stack* path = new stack(); // итоговый путь
    queue* q = new queue(); // очередь из нод на проверку
    std::vector<int> explored = std::vector<int>(nodes.size());
    // 0 если нода не обследована, 1 иначе
    q->enqueue(from, nullptr);
    explored[from] = 1;
    while (!q->is_empty())
    {
        s_node* v = q->dequeue(); // текущая нода на проверку
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
    recolor_path(path);

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
        const unsigned int from = v->val;
        const unsigned int to = v->next->val;
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
        const unsigned int from = v->val;
        const unsigned int to = v->next->val;
        if (edge* orig_edge = get_edge(from, to))
        {
            dynamic_cast<edgeDataFlow*>(orig_edge->data)->flow += min_val;
            update_flow_edge(orig_edge);
        }
        else
        {
            orig_edge = get_edge(to, from);
            dynamic_cast<edgeDataFlow*>(orig_edge->data)->flow -= min_val;
            update_flow_edge(orig_edge);
        }
        v = v->next;
    }
}

void graph::update_flow_edge(edge* orig_edge)
{
    engine->with_commands({
        factory->get_update_edge_flow_label_command(*orig_edge),
        factory->get_recolor_edge_to_red_command(*orig_edge)
    })->step();
    console_pause();
    engine->with_commands({
        factory->get_recolor_edge_to_default_command(*orig_edge)
    })->step();
}

void graph::recolor_path(stack* path) const
{
    if (path->is_empty()) return;
    console_pause();
    const s_node* v = path->top;
    while (v->next)
    {
        const unsigned int from = v->val;
        const unsigned int to = v->next->val;
        const edge* e = get_edge(from, to);
        engine->with_commands({
            factory->get_recolor_edge_to_red_command(*e)
            })->step();
        v = v->next;
    }
    console_pause();
}

void graph::maximize_flow()
{
    console_pause();
    graph* res_net = new graph(engine, factory, nodes.size(), RESIDUAL);
    res_net->start = res_net->nodes[start->id];
    res_net->end = res_net->nodes[end->id];
    stack* path = new stack();

    engine->with_commands({
        factory->get_basic_graph_create_command(res_net)
        })->step();
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

std::vector<node*> graph::get_all_nodes() const
{
    std::vector<node*> result;
    if (start != nullptr)
        result.push_back(start);
    for (auto nod : nodes)
    {
        if ((nod->id != start->id) && (nod->id != end->id))
            result.push_back(nod);
    }
    if (end != nullptr)
        result.push_back(end);
    return result;
}

std::vector<edge*> graph::get_all_edges() const
{
    std::vector<edge*> result;
    std::set<node*> used_nodes;
    std::set<edge*> backwards;

    for (node* nod : nodes)
    {
        for (edge* ed : nod->edges)
        {
            if (ed->type == BIDIRECTIONAL)
            {
                if (used_nodes.find(ed->to) == used_nodes.end())
                {
                    used_nodes.insert(ed->from);
                    result.push_back(ed);
                }
                else
                {
                    if (edge* backward = ed->get_backward(); backward == nullptr
                        ||
                        backwards.find(backward) == backwards.end())
                    {
                        used_nodes.insert(ed->from);
                        result.push_back(ed);
                    }
                    else
                        backwards.insert(backward);
                }
            }
            else
            {
                result.push_back(ed);
            }
        }
    }
    return result;
}

edge* edge::get_backward() const
{
    if (type != BIDIRECTIONAL)
        return nullptr;

    for (edge* edge : to->edges)
    {
        if (edge->from == to && edge->to == from)
            return edge;
    }
    return nullptr;
}
