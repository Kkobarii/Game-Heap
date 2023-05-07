#include "GameLibrary.h"

void GameLibrary::load_games()
{
    games = DataManager::load_library(path);
}

void GameLibrary::save_games()
{
    if (path == "")
    {
        std::cout << "No path specified for saving library!" << std::endl;
        return;
    }
    DataManager::save_library(games, path);
}

void GameLibrary::save_games(std::string other_path)
{
    DataManager::save_library(games, other_path);
}

GameLibrary::GameLibrary()
{
    this->path = "";
    this->games = std::vector<std::shared_ptr<Game>>();
}

GameLibrary::GameLibrary(std::string path) : path(path)
{
    load_games();
}

void GameLibrary::add_game(std::shared_ptr<Game> game)
{
    if (game == nullptr)
        return;

    games.push_back(game);
}

void GameLibrary::add_game(std::shared_ptr<Game> game, int rating)
{
    if (game == nullptr)
        return;

    game->set_user_rating(rating);
    games.push_back(game);
}

void GameLibrary::remove_game(int id)
{
    for (auto g : games)
    {
        if (g->get_steam_id() == id)
        {
            games.erase(std::remove(games.begin(), games.end(), g), games.end());
            break;
        }
    }
}

void GameLibrary::update_game(std::shared_ptr<Game> game)
{
    for (auto g : games)
    {
        if (g->get_steam_id() == game->get_steam_id())
        {
            g = game;
        }
    }
}

std::vector<std::shared_ptr<Game>> GameLibrary::get_games()
{
    return std::vector<std::shared_ptr<Game>>();
}

void GameLibrary::sort_games_by_rating()
{
    std::sort(games.begin(), games.end(), [](std::shared_ptr<Game> a, std::shared_ptr<Game> b) {
        if (get_rating_priority(*a) == get_rating_priority(*b))
            return get_ratio_priority(*a) < get_ratio_priority(*b);
        return get_rating_priority(*a) > get_rating_priority(*b);
    });
}

void GameLibrary::sort_games_by_ratio()
{
    std::sort(games.begin(), games.end(), [](std::shared_ptr<Game> a, std::shared_ptr<Game> b) {
        if (get_ratio_priority(*a) == -1)
            return false;
        if (get_ratio_priority(*b) == -1)
            return true;
        if (get_ratio_priority(*a) == get_ratio_priority(*b))
            return get_rating_priority(*a) > get_rating_priority(*b);
        return get_ratio_priority(*a) < get_ratio_priority(*b);
    });
}
