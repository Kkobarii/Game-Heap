#include "GameFinder.h"

using json = nlohmann::json;

GameFinder::GameFinder(std::string path, int refresh_rate)
{
    this->path = path;
    this->refresh_rate = refresh_rate;

    load_games();
}

void GameFinder::load_games()
{
    games = DataManager::load_games(path, refresh_rate);
}

void GameFinder::save_games()
{
    DataManager::save_games(games, path);
}


std::string GameFinder::search_name(std::string name)
{
    std::cout << "Searching for " << name << "... ";

    std::transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c){ return std::tolower(c); });

    for (auto& game : games)
    {
        std::string game_name = game.first;

        std::transform(game_name.begin(), game_name.end(), game_name.begin(),
            [](unsigned char c){ return std::tolower(c); });

        std::transform(game_name.begin(), game_name.end(), game_name.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (game_name == name)
        {
            std::cout << "Found!" << std::endl;
            return game.first;
        }
    }

    std::cout << "Not found :(" << std::endl;
    return "";
}

int GameFinder::get_game_id(const std::string& name)
{
    if (games.find(name) == games.end() || name == "")
    {
        return -1;
    }
    return games.at(name);
}

std::string GameFinder::get_game_name(int id)
{
    for (auto& game : games)
    {
        if (game.second == id)
        {
            return game.first;
        }
    }

    return "";
}

std::unique_ptr<Game> GameFinder::find_game(std::string name)
{
    std::string game_name = search_name(name);
    int id = get_game_id(game_name);

    if (id == -1)
    {
        std::cout << std::endl;
        return nullptr;
    }

    std::string stream_response;
    std::string hltb_response;

    SteamAPI::get_game(stream_response, std::to_string(id));
    HowLongToBeatAPI::get_game(hltb_response, game_name);

    std::unique_ptr<Game> game = std::make_unique<Game>(parse_api_json_to_game(id, stream_response, hltb_response));

    std::cout << std::endl;

    return game;
}
