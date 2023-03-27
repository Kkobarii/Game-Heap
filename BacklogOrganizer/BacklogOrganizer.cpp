#include "BacklogOrganizer.h"

using std::string;
using std::cout;
using std::endl;
using json = nlohmann::json;

BacklogOrganizer::BacklogOrganizer(std::string path, int refresh_rate)
{
    this->path = path;
    this->refresh_rate = refresh_rate;

    load_games();
}

void BacklogOrganizer::load_games()
{
    games = DataManager::load_games(path);
}

void BacklogOrganizer::save_games()
{
    DataManager::save_games(games, path);
}


std::string BacklogOrganizer::search_name(std::string name)
{
    std::cout << "Searching for " << name << "... ";

    std::transform(name.begin(), name.end(), name.begin(),
        [](unsigned char c){ return std::tolower(c); });

    for (auto& game : games)
    {
        string game_name = game.first;

        std::transform(game_name.begin(), game_name.end(), game_name.begin(),
            [](unsigned char c){ return std::tolower(c); });

        // TODO: implement an actual search algorithm
        if (game_name == name)//game_name.find(name) != std::string::npos)
        {
            std::cout << "Found!" << std::endl;
            return game.first;
        }
    }

    std::cout << "Not found :(" << std::endl;
    return "";
}

int BacklogOrganizer::get_game_id(const std::string& name)
{
    if (games.find(name) == games.end() || name == "")
    {
        return -1;
    }
    return games.at(name);
}

std::string BacklogOrganizer::get_game_name(int id)
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

std::unique_ptr<Game> BacklogOrganizer::find_game(std::string name)
{
    std::string game_name = search_name(name);
    int id = get_game_id(game_name);

    if (id == -1)
    {
        std::cout << std::endl;
        return nullptr;
    }

    // TODO: maybe allow adding games that aren't on steam?

    string stream_response;
    string hltb_response;

    SteamAPI::get_game(stream_response, std::to_string(id));
    HowLongToBeatAPI::get_game(hltb_response, game_name);

    std::unique_ptr<Game> game = std::make_unique<Game>(id, stream_response, hltb_response);

    std::cout << std::endl;

    return game;
}
