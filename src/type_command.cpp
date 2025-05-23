#include "type_command.h"
#include <iostream>
#include "command_factory.h"
#include "command.h"
#include <unistd.h>

void TypeCommand::execute(const std::string& args) {
    const std::string path = "PATH";
    const char* envPath = getenv(path.c_str());

    CommandFactory commandFactory;
    auto command = commandFactory.get(args);
    if(command) {
        std::cout << command->name() << " is a shell " << command->type() << std::endl;
    } 
    else {
        if (envPath != nullptr) {
            std::string pathEnvStr(envPath);
            size_t start = 0, end = 0;
            while ((end = pathEnvStr.find(':', start)) != std::string::npos) {
                std::string dir = pathEnvStr.substr(start, end - start);
                std::string fullPath = dir + "/" + args;
                if (access(fullPath.c_str(), X_OK) == 0) {
                    std::cout << args << " is " << fullPath << std::endl;
                    return;
                }
                start = end + 1;
            }
        }
        std::cout << args << ": not found" << std::endl;
    }
}

std::string TypeCommand::type() {
    return "builtin";
}

std::string TypeCommand::name() {
    return "type";
}