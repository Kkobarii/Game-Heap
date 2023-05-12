#pragma once

#include <iostream>
#define LOGGING_LEVEL 3

struct Logger {
    static void log(std::string message, int level);
};
