#include <iostream>

std::vector<std::string> alphabet;

inline void create_alphabet()
{
    alphabet.clear();
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        alphabet.emplace_back(1, letter);
    }
}

struct s_node {
    int val;
    s_node* next;
    s_node* parent;

    s_node(int val, s_node* next) : val{ val }, next{ next }, parent{ nullptr }  {}
    
    s_node(int val) : val{ val }, next{ nullptr }, parent{ nullptr } {}

    s_node() : val{ 0 }, next{ nullptr }, parent{ nullptr } {}
    
    ~s_node() 
    {
        next = nullptr;
    }

}; 

struct stack {
    s_node* top;

    stack()
    {
        top = nullptr;
    }

    bool is_empty()
    {
        return top == nullptr;
    }

    int pop() {
        if (is_empty()) return INT_MIN;

        s_node* top_node = top;
        int val = top_node->val;
        top = top->next;
        delete top_node;
        return val;
    }

    ~stack()
    {
        while (!is_empty())
        {
            pop();
        }
    }

    void push(int element) {
        s_node* new_node = new s_node(element,top);
        top = new_node;
    }

    s_node* stack_top() {
        return top;
    }

    void show()
    {
        cout << "Stack" << endl;
        s_node* v = top;
        while (v)
        {
            cout << v->val << endl;
            v = v->next;
        }
    }

};

struct queue {
    s_node* front;
    s_node* rear;

    queue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~queue()
    {
        while (!is_empty()) {
            dequeue();
        }
    }

    void enqueue(int value)
    {
        s_node* new_node = new s_node(value);

        if (rear == nullptr) {
            front = rear = new_node;
            return;
        }

        rear->next = new_node;
        rear = new_node;
    }

    void enqueue(int value, s_node* parent)
    {
        enqueue(value);
        rear->parent = parent;
    }

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

    s_node* dequeue()
    {
        if (front == nullptr) {
            return nullptr;
        }

        s_node* front_node = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        return front_node;
    }


    s_node* peek()
    {
        return front;
    }

    bool is_empty()
    {
        return front == nullptr;
    }
};



