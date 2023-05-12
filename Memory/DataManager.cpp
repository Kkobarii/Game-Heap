#include "DataManager.h"

using json = nlohmann::json;

void DataManager::save_games(std::unordered_map<std::string, int> games, std::string path)
{
    if (path == "")
    {
        Logger::log("No path specified for saving library!", 1);
        return;
    }

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
    Logger::log("Loading games", 1);

    std::ifstream file(path);
    json json;
    std::unordered_map<std::string, int> games;

    if (!file.is_open() || !file.good())
    {
        Logger::log("File not found, loading from steam api", 2);

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

        Logger::log("File found, time since last update: " + std::to_string(time_since) + " seconds", 2);

        if (time_since > refresh_rate)
        {
            Logger::log("File too old, loading from steam api", 2);
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
            Logger::log("File recent, loading from file", 2);
            games = json["games"].get<std::unordered_map<std::string, int>>();
        }
    }

    file.close();

    return games;
}

void DataManager::save_library(std::vector<std::shared_ptr<Game>> games, std::string path)
{
    Logger::log("Saving library", 1);

    std::ofstream file(path);

    nlohmann::ordered_json json;
    json["last_updated"] = std::chrono::system_clock::now().time_since_epoch().count();
    json["total_games"] = games.size();

    std::vector<nlohmann::ordered_json> games_json;

    for (auto game : games)
    {
        games_json.push_back(parse_game_to_json(*game));
    }

    json["games"] = games_json;

    file << json.dump(4);

    file.close();
}

std::vector<std::shared_ptr<Game>> DataManager::load_library(std::string path)
{
    Logger::log("Loading library", 1);

    std::ifstream file(path);
    json json;
    std::vector<std::shared_ptr<Game>> games;

    if (!file.is_open())
    {
        Logger::log("File not found", 1);
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
