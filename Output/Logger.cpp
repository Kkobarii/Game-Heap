#include "Logger.h"

void Logger::log(std::string message, int level)
{
    if (level <= LOGGING_LEVEL)
    {
        std::cout << "[LOG] ";
        for (int i = 0; i < level; i++)
            std::cout << "  ";
        std::cout << message << std::endl;
    }
}
