#pragma once
#include "edge_data.h"

class edgeDataSingle : public edgeData
{
public:
    int value{0};

    edgeDataSingle(const int value)
        : edgeData()
        , value{value}
    {
    }

    edgeDataSingle() = default;

    const std::string* to_label() const override
    {
        return new std::string(std::to_string(value));
    }
};
