#include <pwd_command.h>
#include <iostream>
#include <unistd.h>

void PwdCommand::execute(const std::string& args) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << cwd << std::endl;
    } else {
        std::cerr << "Error getting current working directory" << std::endl;
    }
}

std::string PwdCommand::type() {
    return "builtin";
}

std::string PwdCommand::name() {
    return "pwd";
}