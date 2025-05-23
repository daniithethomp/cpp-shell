#include <iostream>
#include <string>

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
            exit(std::stoi(args));
        }
        if (input != "") {
            std::cout << input << ": command not found" << std::endl;
        }
    } while(input != "");
}