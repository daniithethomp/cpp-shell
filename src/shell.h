#pragma once
#include "command_factory.h"
#include <string>

class Shell {
    CommandFactory commandFactory;
public:
    void run();
};