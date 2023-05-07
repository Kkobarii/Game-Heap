#pragma once

#include <iostream>
#include "Game.h"

using json = nlohmann::json;

Game parse_json_to_game(std::string game_string);

std::string parse_game_to_json(Game game);
