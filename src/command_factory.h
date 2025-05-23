#pragma once
#include <map>
#include <memory>
#include <string>
#include "command.h"
#include "exit_command.h"
#include "echo_command.h"
#include "type_command.h"
#include "pwd_command.h"
#include "cd_command.h"

class CommandFactory {
    std::map<std::string, std::unique_ptr<Command>> commands;
public:
    CommandFactory();
    Command* get(const std::string& name);
};