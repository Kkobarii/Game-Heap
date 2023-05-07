#include "DataManager.h"

using json = nlohmann::json;

void DataManager::save_games(std::unordered_map<std::string, int> games, std::string path)
{
    std::ofstream file(path);

    //file <<  std::chrono::system_clock::now().time_since_epoch().count();

    nlohmann::ordered_json json;
    json["last_updated"] = std::chrono::system_clock::now().time_since_epoch().count();
    json["total_games"] = games.size();
    json["games"] = games;


    file << json.dump(4);

    file.close();
}

std::unordered_map<std::string, int> DataManager::load_games(std::string path, int refresh_rate)
{
    std::cout << "Loading games" << std::endl;

    std::ifstream file(path);
    json json;
    std::unordered_map<std::string, int> games;

    if (!file.is_open() || !file.good())
    {
        std::cout << " file not found, loading from steam api" << std::endl;
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
        json = json::parse(file);
        auto time_since = (std::chrono::system_clock::now().time_since_epoch().count() - json["last_updated"].get<long long>()) * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
        std::cout << " time since last update: " << time_since << " seconds" << std::endl;

        if (time_since > refresh_rate)
        {
            std::cout << " file too old, loading from steam api" << std::endl;
            std::string response;
            SteamAPI::get_games(response);
            json = json::parse(response);

            for (auto& element: json["applist"]["apps"])
            {
                games[element["name"]] = element["appid"];
            }

            save_games(games, path);
        }
        else
        {
            std::cout << " file recent, loading from file" << std::endl;
            games = json["games"].get<std::unordered_map<std::string, int>>();
        }
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
        file << parse_game_to_json(*game);
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
            Game g = parse_json_to_game(element.dump());
            games.push_back(std::make_shared<Game>(g));
        }
    }

    return games;
}
