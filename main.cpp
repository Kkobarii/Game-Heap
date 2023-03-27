#include <iostream>
#include "restc-cpp/restc-cpp.h"
#include "restc-cpp/RequestBuilder.h"
#include "json.hpp"
#include "SteamAPI.h"
#include "BacklogOrganizer.h"
#include "DataManager.h"

using namespace std;
using namespace restc_cpp;


int main()
{
    // Backlog organizer
    BacklogOrganizer org = BacklogOrganizer("games.txt");

    // Game library
    GameLibrary lib = GameLibrary("user_games.txt");
    lib.print();
    lib.add_game(org.find_game("Celeste"));
    lib.add_game(org.find_game("Rocket League"));
    lib.add_game(org.find_game("Factorio"));
    lib.add_game(org.find_game("Car Parking 2"));
    lib.add_game(org.find_game("Cyberpunk 2077"));
    lib.add_game(org.find_game("Nonexistent Game"));
    lib.add_game(org.find_game("Terraria"));
    lib.remove_game(org.get_game_id(org.search_name("Factorio")));

    lib.sort_games();

    lib.print();
    lib.print_simple();

    lib.save_games("modified_user_games.txt");

    return 0;
}