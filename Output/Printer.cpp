#include "Printer.h"

void Printer::print(GameLibrary lib)
{
    Logger::log("Printing library", 1);

    std::cout <<  std::endl;

    for (auto game : lib.get_games())
    {
        Printer::print(game);
        std::cout << std::endl;
    }
}

void Printer::print_simple(GameLibrary lib)
{
    Logger::log("Printing library simplified", 1);

    std::cout << std::endl;

    std::cout << " " << CYAN_B << BLACK << std::left << std::setw(10) << "Rating";
    std::cout << std::setw(14) << "Ratio";
    std::cout << std::setw(14) << "Game" << RESET << std::endl;

    for (auto game : lib.get_games())
    {
        std::cout << " ";
        Printer::print_simple(game);
    }
    std::cout << std::endl;
}

void Printer::print(std::shared_ptr<Game> game)
{
    std::cout << " " << CYAN << "### " << game->get_name() << " ###" << RESET << std::endl;

    auto steam_attributes = game->get_steam_attributes();
    std::cout << " " << "Steam";
    if (steam_attributes.has_value())
    {
        std::cout << " ( " << steam_attributes.value().steam_appid << " )" << std::endl;
        std::cout << "   Price: " << steam_attributes.value().price.formatted << std::endl;
        std::cout << "   Rating: " << (steam_attributes.value().rating.has_value() ?
                  std::to_string(steam_attributes.value().rating.value()) : "no rating") << std::endl;
    }
    else
        std::cout << ": no information" << std::endl;

    auto hltb_attributes = game->get_howlongtobeat_attributes();
    std::cout << " " << "HowLongToBeat";
    if (hltb_attributes.has_value())
    {
        std::cout << " ( " << hltb_attributes.value().howlongtobeat_appid << " )" << std::endl;
        std::cout << "   Playtime: " <<  (static_cast<double>(hltb_attributes->completion_main) / 3600) << " hours" << std::endl;
        std::cout << "   Rating: " << (hltb_attributes.value().rating.has_value() ?
                  std::to_string(hltb_attributes.value().rating.value()) : "no rating") << std::endl;
    }
    else
        std::cout << ": no information" << std::endl;

    std::cout << " " << "User data: " << std::endl;
    std::cout << "   Rating: " << (game->get_user_rating().has_value() ? std::to_string(game->get_user_rating().value()) : "null") << std::endl;
    std::cout << "   Note: " << (game->get_description().has_value() ? game->get_description().value() : "null") << std::endl;
}

void Printer::print_simple(std::shared_ptr<Game> game)
{
    std::cout << std::left << std::setw(10) << (double)get_rating_priority(*game)/100;
    std::cout << std::setw(14) << get_ratio_priority(*game);
    std::cout << game->get_name() << std::endl;
}
