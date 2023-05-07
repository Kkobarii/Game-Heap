#include "GameFinder.h"
#include "GameLibrary.h"

// TODO: search algorithm is still perfect match only

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
    GameFinder org = GameFinder("games.txt");

    // Game library
    // Create a library and specify the path to file where the games will be saved
    GameLibrary lib = GameLibrary("user_games.txt");

    // Print the whole library
    lib.print();

    // Add some games to the library
    lib.add_game(org.find_game("Celeste"));
    lib.add_game(org.find_game("Rocket League"));
    lib.add_game(org.find_game("Factorio"));
    lib.add_game(org.find_game("Car Parking 2"));
    lib.add_game(org.find_game("Cyberpunk 2077"), 50);       // adding a game with a user rating
    lib.add_game(org.find_game("//TODO: today"));
    lib.add_game(org.find_game("Nonexistent Game"));                // adding a nonexistent game
    lib.add_game(org.find_game("Terraria"));

    // Remove a game from the library
    lib.remove_game(org.get_game_id(org.search_name("Factorio")));

    // Print the whole library
    lib.print();

    // Sort library by average rating
    lib.sort_games_by_rating();
    lib.print_simple();

    // Sort library by money/hour ratio
    lib.sort_games_by_ratio();
    lib.print_simple();

    // Save the library to a file
    lib.save_games("modified_user_games.txt");

    return 0;
}
