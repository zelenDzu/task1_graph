#pragma once
#include <vector>
#include <edge.h>

class node
{
    public:
        int id;
        std::vector<edge*> edges; //����� ������� ������� �� �������

        node() = default;

        node(int id) : id{ id } {}

        ~node() = default;
};