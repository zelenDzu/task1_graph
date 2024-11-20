#pragma once
#include <iostream>
#include <vector>

inline static std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

struct s_node
{
    int val;
    s_node* next;
    s_node* parent;

    s_node(const int val, s_node* next)
        : val{val}
        , next{next}
        , parent{nullptr}
    {
    }

    s_node(const int val)
        : val{val}
        , next{nullptr}
        , parent{nullptr}
    {
    }

    s_node()
        : val{0}
        , next{nullptr}
        , parent{nullptr}
    {
    }

    ~s_node() { next = nullptr; }
};

struct stack
{
    s_node* top = nullptr;

    stack() = default;

    bool is_empty() const;

    int pop();

    ~stack();

    void push(int element);

    s_node* stack_top();

    void show() const;
};

struct queue
{
    s_node* front = nullptr;
    s_node* rear = nullptr;

    queue() = default;

    ~queue();

    void enqueue(int value);

    void enqueue(int value, s_node* parent);

    /*int dequeue()
    {
        if (front == nullptr) {
            return INT_MIN;
        }

        s_node* temp = front;
        int value = temp->val;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return value;
    }*/

    s_node* dequeue();

    s_node* peek();

    bool is_empty() const;
};
