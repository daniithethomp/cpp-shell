#include "echo_command.h"
#include <iostream>

void EchoCommand::execute(const std::string& args) {
    std::cout << args << std::endl;
}

std::string EchoCommand::type() {
    return "builtin";
}