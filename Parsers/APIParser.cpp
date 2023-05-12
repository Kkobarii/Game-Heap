#include "APIParser.h"

Game parse_api_json_to_game(int id, std::string steam_string, std::string howlongtobeat_string, std::optional<int> user_rating, bool archived)
{
    nlohmann::ordered_json steam_json = nlohmann::ordered_json::parse(steam_string);
    nlohmann::ordered_json hltb_json = nlohmann::ordered_json::parse(howlongtobeat_string);

    std::string name;
    std::optional<SteamAttributes> steam_attributes;
    std::optional<HowLongToBeatAttributes> howlongtobeat_attributes;

    if (steam_json[std::to_string(id)]["success"] == false)
    {
        steam_attributes = std::nullopt;
    }
    else
    {
        steam_attributes = SteamAttributes();

        name = steam_json[std::to_string(id)]["data"]["name"];

        steam_attributes->steam_appid = steam_json[std::to_string(id)]["data"]["steam_appid"];
        if (steam_json[std::to_string(id)]["data"]["price_overview"].is_null())
        {
            steam_attributes->price.amount = -1;
            steam_attributes->price.currency = "N/A";
            steam_attributes->price.formatted = "N/A";
        }
        else
        {
            steam_attributes->price.amount = steam_json[std::to_string(id)]["data"]["price_overview"]["final"];
            steam_attributes->price.currency = steam_json[std::to_string(id)]["data"]["price_overview"]["currency"];
            steam_attributes->price.formatted = steam_json[std::to_string(
                    id)]["data"]["price_overview"]["final_formatted"];
        }
        if (steam_json[std::to_string(id)]["data"]["metacritic"].is_null())
        {
            steam_attributes->rating = std::nullopt;
        }
        else
        {
            steam_attributes->rating = steam_json[std::to_string(id)]["data"]["metacritic"]["score"];
        }
    }

    if (hltb_json["data"].empty())
    {
        howlongtobeat_attributes = std::nullopt;
    }
    else
    {
        howlongtobeat_attributes = HowLongToBeatAttributes();

        howlongtobeat_attributes->howlongtobeat_appid = hltb_json["data"][0]["game_id"];
        howlongtobeat_attributes->completion_main = hltb_json["data"][0]["comp_main"];
        howlongtobeat_attributes->completion_plus = hltb_json["data"][0]["comp_plus"];
        howlongtobeat_attributes->completion_100 = hltb_json["data"][0]["comp_100"];
        howlongtobeat_attributes->rating = hltb_json["data"][0]["review_score"];
    }

    return Game{name, steam_attributes, howlongtobeat_attributes, user_rating};
}
