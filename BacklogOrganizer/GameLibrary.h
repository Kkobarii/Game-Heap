#pragma once

#include "Game.h"
#include <vector>
#include "DataManager.h"
#include "PriorityCalculator.h"

class GameLibrary {
private:
    std::string path;
    std::vector<std::shared_ptr<Game>> games;

public:
    GameLibrary();
    explicit GameLibrary(std::string path);
    ~GameLibrary() = default;

    void load_games();
    void save_games();
    void save_games(std::string other_path);

    void add_game(std::shared_ptr<Game> game);
    void add_game(std::shared_ptr<Game> game, int rating);
    void remove_game(int id);
    void update_game(std::shared_ptr<Game> game);

    std::vector<std::shared_ptr<Game>> get_games();

    void sort_games_by_rating();
    void sort_games_by_ratio();

    void print()
    {
        std::cout << std::endl << "Game Library:" << std::endl;

        for (auto game : games)
        {
            std::cout << *game << std::endl;
            std::cout << "Rating priority: " << (double)get_rating_priority(*game) / 100 << std::endl;
            double ratio = get_ratio_priority(*game);
            if (ratio > 0)
                std::cout << "Ratio priority: " << get_ratio_priority(*game) << " " << game->get_steam_attributes().value().price.currency << " per hour" << std::endl << std::endl;
            else
                std::cout << "Ratio priority: " << "not enough information" << std::endl << std::endl;
        }
    }

    void print_simple()
    {
        std::cout << std::endl << "Game Library:" << std::endl;

        std::cout << std::left << std::setw(10) << "Rating";
        std::cout << std::setw(14) << "Ratio";
        std::cout << "Game" << std::endl;

        for (auto game : games)
        {
            std::cout << std::left << std::setw(10) << (double)get_rating_priority(*game)/100;
            std::cout << std::setw(10) << get_ratio_priority(*game);
            game->print_simple();
        }
        std::cout << std::endl;
    }
};
