#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "json.hpp"
#include "DataManager.h"
#include "HowLongToBeatAPI.h"
#include "APIParser.h"

class GameFinder
{
private:
    std::string path;
    int refresh_rate;

    std::unordered_map<std::string, int> games;

public:
    explicit GameFinder(std::string path, int refresh_rate = 60*24);

    void load_games();
    void save_games();

    std::string search_name(std::string name);

    int get_game_id(const std::string& name);
    std::string get_game_name(int id);

    std::unique_ptr<Game> find_game(std::string name);

    //void set_user_rating(std::string name, int rating);
    //std::vector<Game> getPriorityList();


    void print()
    {
        for (auto& game : games)
        {
            std::cout << game.first << " " << game.second << std::endl;
        }
    }
};
