#pragma once
#include "node.h"
#include "edge.h"
#include "edge_data_flow.h"
#include "edge_data_single.h"
#include "algorithm.h"


class graph
{
    public:
        node* start;
        node* end;
        std::vector<node*> nodes = {}; 

        graph() = default;

        //graph(node* start, node* end) : start{start}, end{end} {}

        graph(int nodes_count) 
        {
            for (int i = 0; i < nodes_count; i++)
            {
                nodes.push_back(new node(i));
            }
            start = nodes.front();
            end = nodes.back();
        }

        ~graph() = default;

        void add_node()
        {
            int id = nodes.size();
            nodes.push_back(new node(id));
        }

        void set_start(int id)
        {
            if (id < nodes.size()) 
                start = nodes[id];
        }

        void set_end(int id)
        {
            if (id < nodes.size())
                end = nodes[id];
        }

        void add_edge_single(int start_id, int end_id, int value, edgeType type = DIRECTIONAL)
        {
            if ((start_id < nodes.size()) && (end_id < nodes.size()))
            {
                node* from = nodes[start_id];
                node* to = nodes[end_id];
                edge* new_edge = new edge(from, to, type, new edgeDataSingle(value));
                from->edges.push_back(new_edge); 
            }
        }

        void add_edge_flow(int start_id, int end_id, int flow, int capacity, edgeType type = DIRECTIONAL)
        {
            if ((start_id < nodes.size()) && (end_id < nodes.size()))
            {
                node* from = nodes[start_id];
                node* to = nodes[end_id];
                edge* new_edge = new edge(from, to, type, new edgeDataFlow(capacity, flow));
                from->edges.push_back(new_edge);
            }
        }

        void clear_edges()
        {
            for (node* v : nodes)
            {
                v->edges.clear();
            }
        }

        void show(bool res = false)
        {
            string alf = (string)"ABCDEFGHIJKLMNOPQ";
            std::cout << "\n\nNodes count: " << nodes.size();
            for (node* v : nodes)
            {
                std::cout << "\nNode " << alf[v->id];
                for (edge* e : v->edges)
                {
                    if (res)
                    {
                        int val = static_cast<edgeDataSingle*>(e->data)->value;
                        std::cout << "\n\t" << alf[e->to->id] << ": " << val;
                    }
                    else
                    {
                        int f = static_cast<edgeDataFlow*>(e->data)->flow;
                        int c = static_cast<edgeDataFlow*>(e->data)->capacity;
                        std::cout << "\n\t" << alf[e->to->id] << ": " << f << "/" << c;
                    }
                    
                }
            }
        }
        
        void update_residual_network(graph* res_net)
        {
            res_net->clear_edges();
            for (node* v : nodes)
            {
                for (edge* e : v->edges)
                {
                    int c = static_cast<edgeDataFlow*>(e->data)->capacity;
                    int f = static_cast<edgeDataFlow*>(e->data)->flow;
                    edgeType type;
                    if ((c - f > 0) && (f > 0)) type = BIDIRECTIONAL;
                    else type = DIRECTIONAL;
                    if (c - f > 0)
                    {
                        res_net->add_edge_single(e->from->id, e->to->id, c - f, type);
                    }
                    if (f > 0)
                    {
                        res_net->add_edge_single(e->to->id, e->from->id, f, type);
                    }
                }
            }
        }

        stack* find_shortest_path(int from, int to)
        {
            node* n_from = nodes[from];
            node* n_to = nodes[to];
            stack* path = new stack(); // final asnwer
            queue* q = new queue(); // queue of nodes to check
            std::vector<int> explored = std::vector<int>(nodes.size()); // 0 if node not explored, 1 otherwise
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
                    } while (v != nullptr);

                    delete q;
                    break;
                }

                bool has_children = false;
                for (edge* e : nodes[v->val]->edges)
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

        stack* find_shortest_path()
        {
            return find_shortest_path(start->id, end->id);
        }

        edge* get_edge(int from, int to)
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

        void apply_augmenting_path(stack* path, graph* res_net)
        {
            if (!path->top) return;
            s_node* v = path->top;
            int min_val = INT_MAX;

            while (v->next)
            {
                int from = v->val;
                int to = v->next->val;
                edge* e = res_net->get_edge(from, to);
                int value = static_cast<edgeDataSingle*>(e->data)->value;
                if (value < min_val) 
                {
                    min_val = value;
                }
                v = v->next;
            }

            v = path->top;
            while (v->next)
            {
                int from = v->val;
                int to = v->next->val;
                edge* orig_edge = get_edge(from, to);
                if (orig_edge)
                {
                    static_cast<edgeDataFlow*>(orig_edge->data)->flow += min_val;
                }
                else
                {
                    orig_edge = get_edge(to, from);
                    static_cast<edgeDataFlow*>(orig_edge->data)->flow -= min_val;
                }
                v = v->next;
            }

        }

        void maximize_flow()
        {
            graph* res_net = new graph(nodes.size());
            res_net->start = res_net->nodes[start->id];
            res_net->end = res_net->nodes[end->id];
            stack* path = new stack();
            do
            {
                apply_augmenting_path(path, res_net);
                update_residual_network(res_net);
                path = res_net->find_shortest_path();
            } while (!path->is_empty());

            delete res_net;
            delete path;
            show();
        }

};