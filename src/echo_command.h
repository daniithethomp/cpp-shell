#pragma once
#include <string>
#include "command.h"

class EchoCommand : public Command {
    public:
        void execute(const std::string& args) override;

        std::string type() override;

        std::string name() override;
};