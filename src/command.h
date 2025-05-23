#pragma once
#include <string>

class Command {
    public:
        virtual ~Command() = default;
        virtual void execute(const std::string& args) = 0;
        virtual std::string type() = 0;
        virtual std::string name() = 0;
};