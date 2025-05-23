#include <iostream>
#include <string>

void do_exit(std::string args) {
    int exit_code = std::stoi(args);
    exit(exit_code);
}

void do_echo(std::string args) {
    std::cout << args << std::endl;
}

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;
    do {
        std::cout << "$ ";
        std::getline(std::cin, input);
        std::string cmd = input.substr(0, input.find(' '));
        std::string args = input.substr(input.find(' ') + 1);
        if (cmd == "exit") {
            do_exit(args);
        }
        else if (cmd == "echo") {
            do_echo(args);
        }
        else if (input != "") {
            std::cout << input << ": command not found" << std::endl;
        }
    } while(input != "");
}