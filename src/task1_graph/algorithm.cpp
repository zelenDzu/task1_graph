#include "other/algorithm.h"

bool stack::is_empty() const
{
    return top == nullptr;
}

int stack::pop()
{
    if (is_empty()) return INT_MIN;

    const s_node* top_node = top;
    int val = top_node->val;
    top = top->next;
    delete top_node;
    return val;
}

stack::~stack()
{
    while (!is_empty())
    {
        pop();
    }
}

void stack::push(const int element)
{
    s_node* new_node = new s_node(element, top);
    top = new_node;
}

s_node* stack::stack_top()
{
    return top;
}

void stack::show() const
{
    std::cout << "Stack" << std::endl;
    const s_node* v = top;
    while (v)
    {
        std::cout << v->val << std::endl;
        v = v->next;
    }
}

queue::~queue()
{
    while (!is_empty())
    {
        dequeue();
    }
}

void queue::enqueue(const int value)
{
    s_node* new_node = new s_node(value);

    if (rear == nullptr)
    {
        front = rear = new_node;
        return;
    }

    rear->next = new_node;
    rear = new_node;
}

void queue::enqueue(const int value, s_node* parent)
{
    enqueue(value);
    rear->parent = parent;
}

s_node* queue::dequeue()
{
    if (front == nullptr)
        return nullptr;

    s_node* front_node = front;
    front = front->next;

    if (front == nullptr)
        rear = nullptr;

    return front_node;
}

s_node* queue::peek()
{
    return front;
}

bool queue::is_empty() const
{
    return front == nullptr;
}