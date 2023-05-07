# Game Heap

Project for my C++ course

## Description
---
Do you have an overwhelming ton of games you want to play but can't be bothered to organize them? Want to know how many
hours are you going to get for your money? Game Heap is a simple and not at all optimized program which tries to fix
this problem.

This program is a simple gaming backlog organizer. It allows the user to add steam games they want to play, sort
them and figure out which are the best ones.

The game priority is calculated based on game reviews, average game time, price and user defined priority, representing the user's desire to play.

The system shows basic information on each game: name, time to beat, reviews and steam price. The user can also add
notes to the games and check which ones they played. Finished games are added to an archive.

All the information is collected using APIs from Steam and HowLongToBeat. Games and user config can be locally saved and
loaded from a JSON document.

## API Usage
---

```cpp
// creates a backlog organizer
GameFinder org = GameFinder("games.txt");

// creates a game library and specifies a path to a document where the games will be loaded from
GameLibrary lib = GameLibrary("user_games.txt");

// adds a game to a library
lib.add_game(org.find_game("Celeste"));
lib.add_game(org.find_game("Rocket League"));
lib.add_game(org.find_game("Factorio"));
lib.add_game(org.find_game("Car Parking 2"));
lib.add_game(org.find_game("Cyberpunk 2077"));
lib.add_game(org.find_game("//TODO: today"));
lib.add_game(org.find_game("Nonexistent Game"));
lib.add_game(org.find_game("Terraria"));

// removes a game from a library
lib.remove_game(org.get_game_id(org.search_name("Factorio")));

// prints all the games in the library
lib.print();

// sorts the library by rating
lib.sort_games_by_rating();

// prints the library in a simplified way
lib.print_simple();

// sorts the library by money/hour ratio
lib.sort_games_by_ratio();

// prints the library in a simplified way
lib.print_simple();

// saves the current library to the specified file
lib.save_games("modified_user_games.txt");
```
