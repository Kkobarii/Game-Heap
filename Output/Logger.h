#pragma once

#include <iostream>
#include "color.h"
#define LOGGING_LEVEL 3

struct Logger {
    static void log(std::string message, int level);
};
