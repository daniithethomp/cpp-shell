#include "command_factory.h"

CommandFactory::CommandFactory() {
        commands["exit"] = std::make_unique<ExitCommand>();
        commands["echo"] = std::make_unique<EchoCommand>();
        commands["type"] = std::make_unique<TypeCommand>();
        commands["pwd"] = std::make_unique<PwdCommand>();
}

Command* CommandFactory::get(const std::string& name) {
    auto it = commands.find(name);
    return it != commands.end() ? it->second.get() : nullptr;
}
