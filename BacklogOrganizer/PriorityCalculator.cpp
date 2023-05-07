#include "PriorityCalculator.h"

int get_rating_priority(Game game)
{
    int priority = 0;
    int count = 0;
    std::optional<SteamAttributes> steam_attributes = game.get_steam_attributes();
    std::optional<HowLongToBeatAttributes> howlongtobeat_attributes = game.get_howlongtobeat_attributes();

    if (game.get_user_rating() != std::nullopt)
    {
        priority += game.get_user_rating().value_or(0);
        count++;
    }

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

    if (game.is_archived())
        priority = 0;

    if (priority < 0)
        priority = 0;

    return priority;
}

double get_ratio_priority(Game game)
{
    std::optional<SteamAttributes> steam_attributes = game.get_steam_attributes();
    std::optional<HowLongToBeatAttributes> howlongtobeat_attributes = game.get_howlongtobeat_attributes();

    if (steam_attributes == std::nullopt)
        return -1;

    if (howlongtobeat_attributes == std::nullopt)
        return -1;

    if (howlongtobeat_attributes->completion_main == 0)
        return (double)steam_attributes->price.amount / 100;

    if (steam_attributes->price.amount == 0 || steam_attributes->price.amount == -1)
        return 0;

    double ratio = ((double)steam_attributes->price.amount / 100) / ((double)howlongtobeat_attributes->completion_main / 3600);

    if (game.is_archived())
        ratio = -1;

    return ratio;
}
