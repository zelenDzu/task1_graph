#pragma once
#include <string>

class edgeData
{
public:
    edgeData() = default;

    virtual ~edgeData() noexcept = default;

    virtual const std::string* to_label() const = 0;
};
