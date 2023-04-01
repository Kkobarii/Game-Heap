#pragma once

#include <iostream>
#include "Game.h"

class APIParser
{
public:
    static Game parse_to_game(int id, std::string steam_string, std::string howlongtobeat_string, std::optional<int> user_rating = std::nullopt, bool archived = false);
    static std::string parse_from_game(Game game);
};
