#pragma once
#include "command_factory.h"
#include <string>

class Shell {
    CommandFactory commandFactory;
public:
    void run();
    bool executeCustomCommand(const std::string& cmd, const std::string& args);
    std::string cleanArgs(const std::string& args);
};