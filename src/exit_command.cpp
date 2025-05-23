#include "exit_command.h"
#include <iostream>

void ExitCommand::execute(const std::string& args) {
    int exit_code = std::stoi(args);
    exit(exit_code);
}

std::string ExitCommand::type() {
    return "builtin";
}
