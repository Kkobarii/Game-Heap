#include "GameLibrary.h"
#include <iostream>

struct Printer {
    static void print(GameLibrary lib);
    static void print_simple(GameLibrary lib);

    static void print(std::shared_ptr<Game> game);
    static void print_simple(std::shared_ptr<Game> game);
};
