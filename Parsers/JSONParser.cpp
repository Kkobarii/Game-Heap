#include "JSONParser.h"
using json = nlohmann::json;

Game parse_json_to_game(std::string game_string)
{
    json game_json = json::parse(game_string);

    std::string name;
    std::optional<SteamAttributes> steam_attributes;
    std::optional<HowLongToBeatAttributes> howlongtobeat_attributes;
    std::optional<int> user_rating;
    bool archived;
    std::optional<std::string> description;

    name = game_json["name"];
    if (game_json["steam_attributes"].is_null())
        steam_attributes = std::nullopt;
    else
    {
        steam_attributes = SteamAttributes();

        steam_attributes->steam_appid = game_json["steam_attributes"]["steam_appid"];
        steam_attributes->price.amount = game_json["steam_attributes"]["price"]["amount"];
        steam_attributes->price.currency = game_json["steam_attributes"]["price"]["currency"];
        steam_attributes->price.formatted = game_json["steam_attributes"]["price"]["formatted"];

        if (game_json["steam_attributes"]["rating"].is_null())  // nejde pouzit v ternarnim operatoru?
            steam_attributes->rating = std::nullopt;
        else
            steam_attributes->rating = game_json["steam_attributes"]["rating"];
    }

    if (game_json["howlongtobeat_attributes"].is_null())
        howlongtobeat_attributes = std::nullopt;
    else
    {
        howlongtobeat_attributes = HowLongToBeatAttributes();

        howlongtobeat_attributes->howlongtobeat_appid = game_json["howlongtobeat_attributes"]["howlongtobeat_appid"];
        howlongtobeat_attributes->completion_main = game_json["howlongtobeat_attributes"]["completion_main"];
        howlongtobeat_attributes->completion_plus = game_json["howlongtobeat_attributes"]["completion_plus"];
        howlongtobeat_attributes->completion_100 = game_json["howlongtobeat_attributes"]["completion_100"];

        if (game_json["howlongtobeat_attributes"]["rating"].is_null())
            howlongtobeat_attributes->rating = std::nullopt;
        else
            howlongtobeat_attributes->rating = game_json["howlongtobeat_attributes"]["rating"];
    }

    if (game_json["user_rating"].is_null())
        user_rating = std::nullopt;
    else
        user_rating = game_json["user_rating"];
    archived = game_json["archived"];

    if (game_json["description"].is_null())
        description = std::nullopt;
    else
        description = game_json["description"];

    return Game{name, steam_attributes, howlongtobeat_attributes, user_rating, archived, description};
}

std::string parse_game_to_json(Game game)
{
    nlohmann::ordered_json json_game;

    json_game["name"] = game.get_name();

    std::optional<SteamAttributes> steam_attributes = game.get_steam_attributes();
    std::optional<HowLongToBeatAttributes> howlongtobeat_attributes = game.get_howlongtobeat_attributes();

    if (steam_attributes.has_value())
    {
        json_game["steam_attributes"]["steam_appid"] = steam_attributes->steam_appid;
        json_game["steam_attributes"]["price"]["amount"] = steam_attributes->price.amount;
        json_game["steam_attributes"]["price"]["currency"] = steam_attributes->price.currency;
        json_game["steam_attributes"]["price"]["formatted"] = steam_attributes->price.formatted;
        if (steam_attributes->rating.has_value())
            json_game["steam_attributes"]["rating"] = steam_attributes->rating.value();
        else
            json_game["steam_attributes"]["rating"] = nullptr;
    }
    else json_game["steam_attributes"] = nullptr;

    if (howlongtobeat_attributes.has_value())
    {
        json_game["howlongtobeat_attributes"]["howlongtobeat_appid"] = howlongtobeat_attributes->howlongtobeat_appid;
        json_game["howlongtobeat_attributes"]["completion_main"] = howlongtobeat_attributes->completion_main;
        json_game["howlongtobeat_attributes"]["completion_plus"] = howlongtobeat_attributes->completion_plus;
        json_game["howlongtobeat_attributes"]["completion_100"] = howlongtobeat_attributes->completion_100;
        if (howlongtobeat_attributes->rating.has_value())
            json_game["howlongtobeat_attributes"]["rating"] = howlongtobeat_attributes->rating.value();
        else
            json_game["howlongtobeat_attributes"]["rating"] = nullptr;
    }
    else json_game["howlongtobeat_attributes"] = nullptr;

    std::optional<int> user_rating = game.get_user_rating();
    if (user_rating.has_value())
        json_game["user_rating"] = user_rating.value();
    else
        json_game["user_rating"] = nullptr;

    json_game["archived"] = game.is_archived();

    std::optional<std::string> description = game.get_description();
    if (description.has_value())
        json_game["description"] = description.value();
    else
        json_game["description"] = nullptr;

    return json_game.dump(4);
}
