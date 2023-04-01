#pragma once

#include "Game.h"
#include <vector>
#include "DataManager.h"

class GameLibrary {
private:
    std::string path;
    std::vector<std::shared_ptr<Game>> games;

public:
    explicit GameLibrary(std::string path);
    ~GameLibrary() = default;

    void load_games();
    void save_games();
    void save_games(std::string other_path);

    void add_game(std::shared_ptr<Game> game);
    void remove_game(int id);
    void update_game(std::shared_ptr<Game> game);

    std::vector<std::shared_ptr<Game>> get_games();

    void sort_games();

    void print()
    {
        std::cout << std::endl << "Game Library:" << std::endl;

        for (auto game : games)
        {
            std::cout << *game << std::endl;
        }
    }

    void print_simple()
    {
        std::cout << std::endl << "Game Library:" << std::endl;

        for (auto game : games)
        {
            game->print_simple();
        }
        std::cout << std::endl;
    }
};
