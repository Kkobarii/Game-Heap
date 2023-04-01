#include "Game.h"

using json = nlohmann::json;

Game::Game(std::string name, std::optional<SteamAttributes> steam_attributes, std::optional<HowLongToBeatAttributes> howlongtobeat_attributes, std::optional<int> user_rating, bool archived) :
    name(name),
    steam_attributes(steam_attributes),
    howlongtobeat_attributes(howlongtobeat_attributes),
    user_rating(user_rating),
    archived(archived)
{
    calculate_priority();
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

void Game::set_user_rating(int rating)
{
    if (rating < 0)
        user_rating = 0;
    else if (rating > 100)
        user_rating = 100;
    user_rating = rating;

    calculate_priority();
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
    priority += user_rating.value_or(0);
    count++;

    if (steam_attributes == std::nullopt)
    {
        priority += 0;
    }
    else
    {
        priority += steam_attributes->rating.value_or(0);
    }
    count++;

    if (howlongtobeat_attributes == std::nullopt)
    {
        priority += 0;
    }
    else
    {
        priority += howlongtobeat_attributes->rating.value_or(0);
    }
    count++;

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
}
