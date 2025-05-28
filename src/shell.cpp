#include "shell.h"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>

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

        args = cleanArgs(args);
        
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

std::string Shell::cleanArgs(const std::string& args) {
    std::vector<std::string> result;
    std::string current;
    bool inQuotes = false;
    bool justClosedQuote = false;

    for(size_t i = 0; i < args.size(); ++i) {
        char c = args[i];
        if (c == '\'') {
            inQuotes = !inQuotes;
            if (!inQuotes) {
                justClosedQuote = true;
            } else if (!current.empty() && !justClosedQuote) {
                result.push_back(current);
                current.clear();
            }
        } else if (std::isspace(c) && !inQuotes) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
            justClosedQuote = false;
        } else {
            current += c;
            justClosedQuote = false;
        }
    }
    if (!current.empty()) {
        if (inQuotes) {
            current = "'" + current;
        }
        result.push_back(current);
    }

    std::string cleanedArgs;
    for(size_t i = 0; i < result.size(); ++i) {
        cleanedArgs += result[i];
        if (i + 1 < result.size()) {
            cleanedArgs += " ";
        }
    }
    return cleanedArgs;
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