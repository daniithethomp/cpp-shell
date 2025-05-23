#pragma once
#include <string>
#include "command.h"

class ExitCommand : public Command {
    public:
        void execute(const std::string& args) override;

        std::string type() override;
};