#include <cd_command.h>
#include <iostream>
#include <unistd.h>

void CdCommand::execute(const std::string& args) {
    std::string path = args;
    if (args[0] == '~') {
        const char* home = getenv("HOME");
        if(home) {
            path = std::string(home) + args.substr(1);
        }
    }
    if (chdir(path.c_str()) != 0) {
        std::cerr << "cd: " << args << ": No such file or directory" << std::endl;
    }
}

std::string CdCommand::type() {
    return "builtin";
}

std::string CdCommand::name() {
    return "cd";
}