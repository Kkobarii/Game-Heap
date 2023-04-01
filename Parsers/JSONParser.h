#pragma once

#include <iostream>
#include "Game.h"

class JSONParser
{
public:
    static Game parse_to_game(std::string json);
    static std::string parse_from_game(Game game);
};
