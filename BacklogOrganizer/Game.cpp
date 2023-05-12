#include "Game.h"

using json = nlohmann::json;

Game::Game(std::string name, std::optional<SteamAttributes> steam_attributes,
           std::optional<HowLongToBeatAttributes> howlongtobeat_attributes,
           std::optional<int> user_rating, std::optional<std::string> description) :
    name(name),
    steam_attributes(steam_attributes),
    howlongtobeat_attributes(howlongtobeat_attributes),
    user_rating(user_rating),
    description(description)
{
}

void Game::set_user_rating(int rating)
{
    if (rating < 0 || rating > 100)
        user_rating = std::nullopt;
    else
        user_rating = rating;
}

void Game::set_description(std::string description)
{
    if (description.empty())
        this->description = std::nullopt;
    else
        this->description = description;
}

int Game::get_steam_id()
{
    if (steam_attributes == std::nullopt)
        return -1;
    else
        return steam_attributes->steam_appid;
}
