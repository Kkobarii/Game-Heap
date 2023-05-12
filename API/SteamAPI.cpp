#include "SteamAPI.h"

int SteamAPI::get(std::string url, std::unordered_map<std::string, std::string> arguments, std::string& response)
{
    std::string message = "SteamAPI::get() called with url: " + url;

    if (arguments.size() > 0)
    {
        message += "?";
        bool first = true;
        for (auto& argument : arguments)
        {
            if (!first)
                message += "&";
            else
                first = false;
            message += argument.first + "=" + argument.second;
        }
    }
    Logger::log(message, 2);

    int responseCode = 0;

    auto rest_client = restc_cpp::RestClient::Create();
    rest_client->Process
    ([=, &response, &responseCode]
        (restc_cpp::Context& ctx)
        {
        restc_cpp::RequestBuilder builder(ctx);
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
    arguments["cc"]="eur";

    return get(url, arguments,  response);
}
