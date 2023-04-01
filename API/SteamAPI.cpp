//
// Created by barca on 18.3.23.
//

#include "SteamAPI.h"

using namespace restc_cpp;

//void SteamAPI::read_key(std::string filename)
//{
//    std::ifstream file(filename);
//
//    if (!file.is_open())
//        throw std::runtime_error("Could not open file: " + filename);
//
//    std::string line;
//    while (std::getline(file, line))
//    {
//        key += line;
//    }
//    file.close();
//
//    std::cout << "Steam API key: " << key << std::endl;
//}

int SteamAPI::get(std::string url, std::unordered_map<std::string, std::string> arguments, std::string& response)
{
    std::cout << "SteamAPI::get() called with url: " << url;
    if (arguments.size() > 0)
    {
        std::cout << "?";
        bool first = true;
        for (auto& argument : arguments)
        {
            if (!first)
                std::cout << "&";
            else
                first = false;
            std::cout << argument.first << "=" << argument.second;
        }
    }
    std::cout << std::endl;

    int responseCode = 0;

    auto rest_client = RestClient::Create();
    rest_client->Process
    ([=, &response, &responseCode]
        (Context& ctx)
        {
        RequestBuilder builder(ctx);
        builder.Get(url);

        for (auto& argument : arguments)
        {
            builder.Argument(argument.first, argument.second);
        }

        auto reply = builder.Execute();

        response = reply->GetBodyAsString();
        responseCode = reply->GetResponseCode();
    });

    return responseCode;
}

int SteamAPI::get_games(std::string& response)
{
    std::string url = "https://api.steampowered.com/ISteamApps/GetAppList/v0002/";

    std::unordered_map<std::string, std::string> arguments;
    arguments["format"] = "json";

    return get(url, arguments, response);
}

int SteamAPI::get_game(std::string& response, std::string appid)
{
    std::string url = "https://store.steampowered.com/api/appdetails/";

    std::unordered_map<std::string, std::string> arguments;
    arguments["appids"] = appid;
    // TODO: add currency option
    arguments["cc"]="eur";

    return get(url, arguments,  response);
}
