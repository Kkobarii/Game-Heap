# Game Heap
> Project for my C++ course

## Description
---
Do you have an overwhelming ton of games you want to play but can't be bothered to organize them? Want to know how many hours are you going to get for your money? Game Heap is a simple and not at all optimized program which tries to fix this problem.

This program is a simple gaming backlog organizer. It will allow the user to add games they want to play, sort them and figure out which are the best ones.

The game priority is calculated based on game reviews, average game time, price and user defined priority, representing the user's desire to play. The weight of all these attributes can be modified according to the user's preferences.

The system shows basic information on each game: name, time to beat, reviews and steam price. The user can also add notes to the games and check which ones they played. Finished games are added to an archive.

All the information is collected using APIs from Steam and HowLongToBeat. Games and user config can be locally saved and loaded from a JSON document.

## API Usage
---
```cpp

// creates a backlog organizer
BacklogOrganizer org = BacklogOrganizer("games.txt");

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

// sorts the library
lib.sort_games();

// prints all the games in the library
lib.print();

// prints the library in a simplified way (priority: game name)
lib.print_simple();

// saves the current library to 
lib.save_games("modified_user_games.txt");

```
