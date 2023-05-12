#pragma once

#include <iostream>
#include "Game.h"

using ordered_json = nlohmann::ordered_json;

Game parse_json_to_game(std::string game_string);

ordered_json parse_game_to_json(Game game);
