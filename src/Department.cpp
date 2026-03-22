#include "Department.h"

Department::Department(std::string name, std::string address)
    : name_(std::move(name)), address_(std::move(address)) {}

const std::string& Department::getName() const {
    return name_;
}

const std::string& Department::getAddress() const {
    return address_;
}
