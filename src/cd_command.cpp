#include <cd_command.h>
#include <iostream>
#include <unistd.h>

void CdCommand::execute(const std::string& args) {
    if (chdir(args.c_str()) != 0) {
        std::cerr << "cd " << args << ": No such file or directory" << std::endl;
    }
}

std::string CdCommand::type() {
    return "builtin";
}

std::string CdCommand::name() {
    return "cd";
}