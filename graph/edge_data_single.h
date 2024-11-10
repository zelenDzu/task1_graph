#pragma once
#include "edge_data.h"

class edgeDataSingle : public edgeData
{
    public:
        int value;

        edgeDataSingle(int value) : edgeData(), value{value} {}

        edgeDataSingle() = default;

        ~edgeDataSingle() = default;

        virtual const std::string* to_label() const override 
        {
            const std::string result = std::to_string(value);
            return new std::string(result);
        }
};