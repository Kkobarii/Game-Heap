#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <fstream>
#include "SteamAPI.h"
#include "JSONParser.h"
#include "Game.h"
#include "Logger.h"

class DataManager
{
public:
    static void save_games(std::unordered_map<std::string, int> games, std::string path);
    static std::unordered_map<std::string, int> load_games(std::string path, int refresh_rate);

    static void save_library(std::vector<std::shared_ptr<Game>> games, std::string path);
    static std::vector<std::shared_ptr<Game>> load_library(std::string path);
};
