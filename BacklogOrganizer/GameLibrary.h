#pragma once

#include <vector>
#include "Game.h"
#include "DataManager.h"
#include "PriorityCalculator.h"
#include "Logger.h"

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
    void add_game(std::shared_ptr<Game> game, std::string note);
    void add_game(std::shared_ptr<Game> game, int rating, std::string note);

    void remove_game(int id);
    void update_game(std::shared_ptr<Game> game);
    void update_game(int id, int rating, std::string note);

    void sort_games_by_rating();
    void sort_games_by_ratio();

    std::vector<std::shared_ptr<Game>> get_games() { return games; }
};
