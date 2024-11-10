#pragma once
#include "edge_data.h"

class edgeDataFlow: public edgeData
{
    public:
        int flow;
        int capacity;

        edgeDataFlow(int capacity, int flow) : edgeData(), capacity{capacity}, flow{flow} {}

        edgeDataFlow() = default;

        ~edgeDataFlow() = default;

        virtual const std::string* to_label() const override 
        {
            const std::string result = std::to_string(capacity) + "/" + std::to_string(flow);
            return new std::string(result);
        }
};