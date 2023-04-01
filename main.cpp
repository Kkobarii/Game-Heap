#include <iostream>
#include "BacklogOrganizer.h"
#include "GameLibrary.h"

// TODO: implement a way for the user to set priorities for sorting games
//  - figure out how the games will be sorted
//  - save and load the sorting priorities

// TODO (maybe): implement adding notes to games

// TODO (maybe): add option to exclude adult games from search results
//  - steam has so many of them

// TODO: client interface
//  - will do this last

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
    lib.add_game(org.find_game("//TODO: today"));
    lib.add_game(org.find_game("Nonexistent Game"));
    lib.add_game(org.find_game("Terraria"));
    lib.remove_game(org.get_game_id(org.search_name("Factorio")));

    lib.sort_games();

    lib.print();
    lib.print_simple();

    lib.save_games("modified_user_games.txt");

    return 0;
}
