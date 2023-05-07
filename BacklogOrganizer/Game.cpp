#include "Game.h"

using json = nlohmann::json;

Game::Game(std::string name, std::optional<SteamAttributes> steam_attributes,
           std::optional<HowLongToBeatAttributes> howlongtobeat_attributes,
           std::optional<int> user_rating, bool archived, std::optional<std::string> description) :
    name(name),
    steam_attributes(steam_attributes),
    howlongtobeat_attributes(howlongtobeat_attributes),
    user_rating(user_rating),
    archived(archived),
    description(description)
{
}

std::ostream& operator<<(std::ostream& ostr, const Game& game)
{
    ostr << "/------------------/" << std::endl;

    ostr << "Name: " << game.name << std::endl;
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

    if (game.description.has_value())
        ostr << "Description: " << game.description.value() << std::endl;
    else
        ostr << "Description: N/A" << std::endl;

    return ostr;
}

void Game::set_user_rating(int rating)
{
    if (rating < 0)
        user_rating = 0;
    else if (rating > 100)
        user_rating = 100;
    user_rating = rating;
}

int Game::get_steam_id()
{
    if (steam_attributes == std::nullopt)
        return -1;
    else
        return steam_attributes->steam_appid;
}
