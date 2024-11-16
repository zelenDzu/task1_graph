#pragma once
#include <string>

class edgeData
{
public:
    edgeData() = default;

    virtual ~edgeData() noexcept = default;

    virtual const std::string* to_label() const = 0;
};

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
