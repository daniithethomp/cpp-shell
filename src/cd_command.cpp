#include <cd_command.h>
#include <iostream>
#include <unistd.h>

void CdCommand::execute(const std::string& args) {
    int first_slash = args.find_first_of('/');
    std::string first_dir = args.substr(0, first_slash);
    if (first_dir == "~") {
       chdir((getenv("HOME")+"/"+args.substr(first_slash)).c_str());
    }
    else if (chdir(args.c_str()) != 0) {
        std::cerr << "cd: " << args << ": No such file or directory" << std::endl;
    }
}

std::string CdCommand::type() {
    return "builtin";
}

std::string CdCommand::name() {
    return "cd";
}