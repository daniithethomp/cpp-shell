#include "shell.h"
#include <iostream>
#include <sstream>

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
        if (start != std::string::npos) {
            args = args.substr(start);
        } else {
            args.clear();
        }
        
        if(auto* command = commandFactory.get(cmd)) {
            command->execute(args);
        } else {
            std::cout << cmd << ": command not found" << std::endl;
        }
    }
};