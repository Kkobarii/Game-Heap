#include "GameFinder.h"
#include "GameLibrary.h"
#include "CLI11.hpp"
#include "Printer.h"

void api_demo()
{
    // Backlog organizer
    GameFinder fin = GameFinder("games.txt");

    // Game library
    // Create a library and specify the path to file where the games will be saved
    GameLibrary lib = GameLibrary("user_games.txt");

    // Print the whole library
    Printer::print(lib);

    // Add some games to the library
    lib.add_game(fin.find_game("Celeste"));
    lib.add_game(fin.find_game("Rocket League"));
    lib.add_game(fin.find_game("Factorio"));
    lib.add_game(fin.find_game("Car Parking 2"));
    lib.add_game(fin.find_game("Cyberpunk 2077"), 50);       // adding a game with a user rating
    lib.add_game(fin.find_game("//TODO: today"));
    lib.add_game(fin.find_game("Nonexistent Game"));                // adding a nonexistent game
    lib.add_game(fin.find_game("Terraria"));

    // Remove a game from the library
    lib.remove_game(fin.get_game_id(fin.search_name("Factorio")));

    // Print the whole library
    Printer::print(lib);

    // Sort library by average rating
    lib.sort_games_by_rating();
    Printer::print_simple(lib);

    // Sort library by money/hour ratio
    lib.sort_games_by_ratio();
    Printer::print_simple(lib);

    // Save the library to a file
    lib.save_games("modified_user_games.txt");
}

void create_library(std::string user_games_file)
{
    GameLibrary lib = GameLibrary(user_games_file);

    lib.save_games(user_games_file);
}

void add(std::string game_name, std::string games_file, std::string user_games_file, int user_rating, std::string user_note)
{
    GameFinder fin = GameFinder(games_file);
    GameLibrary lib = GameLibrary(user_games_file);

    lib.add_game(fin.find_game(game_name), user_rating, user_note);
    lib.save_games(user_games_file);
}

void remove(std::string game_name, std::string games_file, std::string user_games_file)
{
    GameFinder fin = GameFinder(games_file);
    GameLibrary lib = GameLibrary(user_games_file);

    lib.remove_game(fin.get_game_id(fin.search_name(game_name)));
    lib.save_games(user_games_file);
}

void update(std::string game_name, std::string games_file, std::string user_games_file, int user_rating, std::string user_note)
{
    GameFinder fin = GameFinder(games_file);
    GameLibrary lib = GameLibrary(user_games_file);

    lib.update_game(fin.get_game_id(fin.search_name(game_name)), user_rating, user_note);
    lib.save_games(user_games_file);
}

void print(std::string user_games_file)
{
    GameLibrary lib = GameLibrary(user_games_file);
    Printer::print(lib);
}

void print_simple(std::string user_games_file)
{
    GameLibrary lib = GameLibrary(user_games_file);
    Printer::print_simple(lib);
}

void sort(std::string user_games_file, CLI::Option* rating, CLI::Option* ratio)
{
        GameLibrary lib = GameLibrary(user_games_file);
        if (*rating)
            lib.sort_games_by_rating();
        else if (*ratio)
            lib.sort_games_by_ratio();
        lib.save_games(user_games_file);
}


int main(int argc, char** argv)
{
    CLI::App app{"Game Library Organizer"};

    auto demo = app.add_subcommand("demo", "Run the demo");
    demo->callback(api_demo);

    std::string user_games_file = "user_games.txt";
    std::string games_file = "games.txt";
    std::string game_name;
    std::string user_note;
    int user_rating = -1;

    auto sub_create = app.add_subcommand("create", "Create a new library");
    sub_create->add_option("path", user_games_file, "Path to file with user games");
    sub_create->callback([&user_games_file]() { create_library(user_games_file); });

    auto sub_add = app.add_subcommand("add", "Add a game to the library");
    sub_add->add_option("game", game_name, "Name of the game to add")->required();
    sub_add->add_option("-g,--games", games_file, "Path to file with games")->check(CLI::ExistingFile);
    sub_add->add_option("-u,--user-games", user_games_file, "Path to file with user games")->check(CLI::ExistingFile);
    sub_add->add_option("-r,--rating", user_rating, "User rating")->check(CLI::Range(0, 100));
    sub_add->add_option("-n,--note", user_note, "User note");
    sub_add->callback([&game_name, &games_file, &user_games_file, &user_rating, &user_note]() { add(game_name, games_file, user_games_file, user_rating, user_note); });

    auto sub_rem = app.add_subcommand("remove", "Remove a game from the library");
    sub_rem->add_option("game", game_name, "Name of the game to remove")->required();
    sub_rem->add_option("-g,--games", games_file, "Path to file with games")->check(CLI::ExistingFile);
    sub_rem->add_option("-u,--user-games", user_games_file, "Path to file with user games")->check(CLI::ExistingFile);
    sub_rem->callback([&game_name, &games_file, &user_games_file]() { remove(game_name, games_file, user_games_file); });

    auto sub_upd = app.add_subcommand("update", "Update a game in the library");
    sub_upd->add_option("game", game_name, "Name of the game to update")->required();
    sub_upd->add_option("-g,--games", games_file, "Path to file with games")->check(CLI::ExistingFile);
    sub_upd->add_option("-u,--user-games", user_games_file, "Path to file with user games")->check(CLI::ExistingFile);
    sub_upd->add_option("-r,--rating", user_rating, "User rating")->check(CLI::Range(0, 100));
    sub_upd->add_option("-n,--note", user_note, "User note");
    sub_upd->callback([&game_name, &games_file, &user_games_file, &user_rating, &user_note]() { update(game_name, games_file, user_games_file, user_rating, user_note); });

    auto sub_print = app.add_subcommand("print", "List all games in the library");
    sub_print->add_option("-u,--user-games", user_games_file, "Path to file with user games")->check(CLI::ExistingFile);
    sub_print->callback([&user_games_file]() { print(user_games_file); });

    auto sub_print_simple = app.add_subcommand("print-simple", "List all games in the library in a simple table");
    sub_print_simple->add_option("-u,--user-games", user_games_file, "Path to file with user games")->check(CLI::ExistingFile);
    sub_print_simple->callback([&user_games_file]() { print_simple(user_games_file); });

    auto sub_sort = app.add_subcommand("sort", "Sort the library");
    sub_sort->add_option("-u,--user-games", user_games_file, "Path to file with user games")->check(CLI::ExistingFile);
    auto rating = sub_sort->add_flag("-r,--rating", "Sort by average rating");
    auto ratio = sub_sort->add_flag("-m,--money-per-hour", "Sort by money/hour ratio");
    sub_sort->callback([&user_games_file, &rating, &ratio]() { sort(user_games_file, rating, ratio); });

    app.require_subcommand(1);

    CLI11_PARSE(app, argc, argv);

    return 0;
}
