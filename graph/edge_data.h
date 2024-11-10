#pragma once
#include <string>

class edgeData
{
    public: 
        edgeData() = default;

        ~edgeData() = default;

        virtual const std::string* to_label() const = 0;
};