#include "DataManager.h"

using json = nlohmann::json;

void DataManager::save_games(std::unordered_map<std::string, int> games, std::string path)
{
    std::ofstream file(path);

    // TODO: add logic to check if file is recent
    //file <<  std::chrono::system_clock::now().time_since_epoch().count();

    json json(games);

    file << json.dump(4);

    file.close();
}

std::unordered_map<std::string, int> DataManager::load_games(std::string path)
{
    std::ifstream file(path);
    json json;
    std::unordered_map<std::string, int> games;

    if (!file.is_open())
    {
        std::string response;
        SteamAPI::get_games(response);
        json = json::parse(response);

        for (auto& element : json["applist"]["apps"])
        {
            games[element["name"]] = element["appid"];
        }

        save_games(games, path);
    }
    else
    {
        file >> json;
        games = json.get<std::unordered_map<std::string, int>>();
    }

    file.close();

    return games;
}

void DataManager::save_library(std::vector<std::shared_ptr<Game>> games, std::string path)
{
    std::cout << "Saving library" << std::endl;

    std::ofstream file(path);

    file << "{\n";
    file << "\t\"last_updated\": " << std::chrono::system_clock::now().time_since_epoch().count() << ",\n";
    file << "\t\"total_games\": " << games.size() << ",\n";
    file << "\t\"games\": [\n";

    bool first = true;
    for (auto game : games)
    {
        if (!first)
        {
            file << "," << std::endl;
        }
        else
        {
            first = false;
        }
        file << game->to_json();
    }

    file << "\n\t]\n}" << std::endl;

    file.close();
}

std::vector<std::shared_ptr<Game>> DataManager::load_library(std::string path)
{
    std::cout << "Loading library" << std::endl;

    std::ifstream file(path);
    json json;
    std::vector<std::shared_ptr<Game>> games;

    if (!file.is_open())
    {
        std::cout << "Library not found" << std::endl;
        return games;
    }
    else
    {
        file >> json;
        for (auto& element : json["games"])
        {
            Game g = Game(element.dump());
            games.push_back(std::make_shared<Game>(g));
        }
    }

    return games;
}
