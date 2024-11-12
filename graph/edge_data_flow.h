#pragma once
#include "edge_data.h"

class edgeDataFlow : public edgeData
{
public:
    int flow{0};
    int capacity{0};

    edgeDataFlow(const int capacity, const int flow)
        : edgeData()
        , flow{flow}
        , capacity{capacity}
    {
    }

    edgeDataFlow() = default;

    const std::string* to_label() const override
    {
        const std::string result = std::to_string(capacity) + "/" +
            std::to_string(flow);
        return new std::string(result);
    }
};
