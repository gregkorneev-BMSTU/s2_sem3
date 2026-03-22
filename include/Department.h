#pragma once

#include <string>

class Department {
public:
    Department(std::string name, std::string address);

    const std::string& getName() const;
    const std::string& getAddress() const;

private:
    std::string name_;
    std::string address_;
};
