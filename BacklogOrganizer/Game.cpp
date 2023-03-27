#include "Game.h"

using json = nlohmann::json;

Game::Game(std::string name, std::optional<SteamAttributes> steam_attributes, std::optional<HowLongToBeatAttributes> howlongtobeat_attributes) :
    name(name),
    steam_attributes(steam_attributes),
    howlongtobeat_attributes(howlongtobeat_attributes)
{
}

Game::Game(int id, std::string steam_string, std::string howlongtobeat_string)
{
    nlohmann::ordered_json steam_json = nlohmann::ordered_json::parse(steam_string);
    nlohmann::ordered_json hltb_json = nlohmann::ordered_json::parse(howlongtobeat_string);

//    std::cout << steam_json.dump(4) << std::endl;
//    std::cout << hltb_json.dump(4) << std::endl;

//    std::cout << id << " " << hltb_json["data"][0]["profile_steam"] << std::endl;

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

    user_rating = std::nullopt;
    archived = false;
}

Game::Game(std::string game_string)     // je lepsi mezi funkcemi posilat string nebo json object?
{
    json game_json = json::parse(game_string);

//    std::cout << game_json.dump(4) << std::endl;

    name = game_json["name"];
    priority = 0;
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
}

std::ostream& operator<<(std::ostream& ostr, const Game& game)
{
    ostr << "/------------------/" << std::endl;

    ostr << "Name: " << game.name << std::endl;
    ostr << "Priority: " << static_cast<double>(game.priority)/100 << std::endl;
    ostr << "Steam" << std::endl;
    if (game.steam_attributes.has_value())
    {
        ostr << "\tAppID: " << game.steam_attributes->steam_appid << std::endl;
        ostr << "\tPrice: " << game.steam_attributes->price.formatted << std::endl;
        if (game.steam_attributes->rating.has_value())
            ostr << "\tRating: " << game.steam_attributes->rating.value() << std::endl;
        else
            ostr << "\tRating: N/A" << std::endl;
    }
    else
    {
        ostr << "\tN/A" << std::endl;
    }
    ostr << "HowLongToBeat" << std::endl;
    if (game.howlongtobeat_attributes.has_value())
    {
        ostr << "\tAppID: " << game.howlongtobeat_attributes->howlongtobeat_appid << std::endl;
        ostr << "\tCompletion Main: " << (static_cast<double>(game.howlongtobeat_attributes->completion_main) / 3600) << " hours" << std::endl;
        ostr << "\tCompletion Plus: " << (static_cast<double>(game.howlongtobeat_attributes->completion_plus) / 3600) << " hours" << std::endl;
        ostr << "\tCompletion 100: " << (static_cast<double>(game.howlongtobeat_attributes->completion_100) / 3600) << " hours" << std::endl;
        ostr << "\tRating: " << game.howlongtobeat_attributes->rating.value_or(-1) << std::endl;
    }
    else
    {
        ostr << "\tN/A" << std::endl;
    }

    if (game.user_rating.has_value())
        ostr << "User Rating: " << game.user_rating.value() << std::endl;
    else
        ostr << "User Rating: N/A" << std::endl;
    ostr << "Archived: " << game.archived << std::endl;

    return ostr;
}

std::string Game::to_json()
{
    nlohmann::ordered_json json_game;

    json_game["name"] = name;
    json_game["priority"] = priority;

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

    if (user_rating.has_value())
        json_game["user_rating"] = user_rating.value();
    else
        json_game["user_rating"] = nullptr;
    json_game["archived"] = archived;

    return json_game.dump(4);
}

void Game::set_user_rating(int rating)
{
    if (rating < 0)
        rating = 0;
    else if (rating > 100)
        rating = 100;
    rating = rating;
}

int Game::get_steam_id()
{
    if (steam_attributes == std::nullopt)
        return -1;
    else
        return steam_attributes->steam_appid;
}

void Game::calculate_priority()
{
    // TODO: make this more sophisticated
    //  - any rating is better than no rating - penalty for no rating or just zero?
    //  - add a weight to each rating - later

    priority = 0;
    int count = 0;
//    std::cout << "Calculating priority for " << name << std::endl;
    if (user_rating != std::nullopt)
    {
//        std::cout << " User rating: " << user_rating.value() << std::endl;
        priority += user_rating.value();
        count++;
    }
    if (steam_attributes != std::nullopt && steam_attributes->rating != std::nullopt)
    {
//        std::cout << " Steam rating: " << steam_attributes->rating.value() << std::endl;
        priority += steam_attributes->rating.value();
        count++;
    }
    if (howlongtobeat_attributes != std::nullopt && howlongtobeat_attributes->rating != std::nullopt)
    {
//        std::cout << " HowLongToBeat rating: " << howlongtobeat_attributes->rating.value() << std::endl;
        priority += howlongtobeat_attributes->rating.value();
        count++;
    }

    if (count == 0)
        count = 1;

    priority *= 100;
    priority /= count;

    if (archived)
        priority = 0;

    if (priority > 10000)
        priority = 10000;

    if (priority < 0)
        priority = 0;

//    std::cout << " Priority: " << priority << std::endl;
//    std::cout << std::endl;
}

int Game::get_priority()
{
    return priority;
}
