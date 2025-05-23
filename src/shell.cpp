#include "shell.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

void Shell::run() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;
    while (true) {
        std::cout << "$ ";
        if(!std::getline(std::cin, input) || input.empty()) {
            break;
        }
        std::istringstream iss(input);
        std::string cmd, args;
        iss >> cmd;
        std::getline(iss, args);

        // trim leading whitespace
        size_t start = args.find_first_not_of(" ");
        args = args.substr(args.find_first_of("'"), args.find_last_of("'")-1);
        if (start != std::string::npos) {
            args = args.substr(start);
        } else {
            args.clear();
        }
        
        if(auto* command = commandFactory.get(cmd)) {
            command->execute(args);
        } else {
            bool customCommandFound = executeCustomCommand(cmd, args);
            if (!customCommandFound) {
                std::cout << cmd << ": command not found" << std::endl;
            }
        }
    }
};

bool Shell::executeCustomCommand(const std::string& cmd, const std::string& args) {
    const std::string path = "PATH";
    const char* envPath = getenv(path.c_str());

    if (envPath != nullptr) {
        std::string pathEnvStr(envPath);
        size_t start = 0, end = 0;
        while ((end = pathEnvStr.find(':', start)) != std::string::npos) {
            std::string dir = pathEnvStr.substr(start, end - start);
            std::string fullPath = dir + "/" + cmd;
            if (access(fullPath.c_str(), X_OK) == 0) {
                system((cmd + " " + args).c_str());
                return true;
            }
            start = end + 1;
        }
    }
    return false;
};