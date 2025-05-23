#include "type_command.h"
#include <iostream>
#include "command_factory.h"
#include "command.h"

void TypeCommand::execute(const std::string& args) {
    CommandFactory commandFactory;
    auto command = commandFactory.get(args);
    if(command) {
        std::cout << command->name() << " is a shell " << command->type() << std::endl;
    } else {
        std::cout << args << ": not found" << std::endl;
    }
}

std::string TypeCommand::type() {
    return "builtin";
}

std::string TypeCommand::name() {
    return "type";
}