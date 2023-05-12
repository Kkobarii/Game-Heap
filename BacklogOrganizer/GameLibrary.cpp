#include "GameLibrary.h"
#include "Logger.h"

void GameLibrary::load_games()
{
    games = DataManager::load_library(path);
}

void GameLibrary::save_games()
{
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

void GameLibrary::add_game(std::shared_ptr<Game> game, int rating, std::string note)
{
    if (game == nullptr)
        return;

    Logger::log("Adding " + game->get_name(), 1);

    game->set_user_rating(rating);

    if (note != "")
        game->set_description(note);


    for (auto g : games)
    {
        if (g->get_steam_id() == game->get_steam_id())
        {
            Logger::log("ADD: Updating " + g->get_name(), 2);
            games.erase(std::remove(games.begin(), games.end(), g), games.end());
            games.push_back(game);
            return;
        }
    }

    Logger::log("ADD: Adding " + game->get_name(), 2);
    games.push_back(game);
}

void GameLibrary::remove_game(int id)
{
    Logger::log("Removing game with id " + std::to_string(id), 1);

    std::vector<std::shared_ptr<Game>> to_remove;
    for (auto g : games)
    {
        if (g->get_steam_id() == id)
        {
            to_remove.push_back(g);
        }
    }

    for (auto g : to_remove)
    {
        Logger::log("REM: Removing " + g->get_name(), 2);
        games.erase(std::remove(games.begin(), games.end(), g), games.end());
    }
}

void GameLibrary::update_game(std::shared_ptr<Game> game)
{
    Logger::log("Updating game " + game->get_name(), 1);

    for (auto g : games)
    {
        if (g->get_steam_id() == game->get_steam_id())
        {
            g = game;
        }
    }
}

void GameLibrary::update_game(int id, int rating, std::string note)
{
    Logger::log("Updating game with id " + std::to_string(id), 1);

    for (auto g : games)
    {
        if (g->get_steam_id() == id)
        {
            Logger::log("UPD: Updating " + g->get_name() + " with rating " + std::to_string(rating) + " and note " + note, 2);
            g->set_user_rating(rating);
            g->set_description(note);
        }
    }
}

void GameLibrary::sort_games_by_rating()
{
    Logger::log("Sorting games by rating", 1);
    std::sort(games.begin(), games.end(), [](std::shared_ptr<Game> a, std::shared_ptr<Game> b) {
        if (get_rating_priority(*a) == get_rating_priority(*b))
            return get_ratio_priority(*a) < get_ratio_priority(*b);
        return get_rating_priority(*a) > get_rating_priority(*b);
    });
}

void GameLibrary::sort_games_by_ratio()
{
    Logger::log("Sorting games by ratio", 1);
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
