#pragma once

#include <iostream>
#include "Game.h"

Game parse_api_json_to_game(int id, std::string steam_string, std::string howlongtobeat_string, std::optional<int> user_rating = std::nullopt, bool archived = false);
