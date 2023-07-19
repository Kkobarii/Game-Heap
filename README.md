# Game Heap

Project for my C++1 course

## Description

Do you have an overwhelming ton of games you want to play but can't be bothered to organize them? Want to know how many hours are you going to get for your money? Game Heap is a simple and not at all optimized program which tries to fix this problem.

This program is a simple gaming backlog organizer. It allows the user to add steam games they want to play, sort them and figure out which are the best ones.

The game priority is calculated based on game reviews, average game time, price and user defined priority, representing the user's desire to play. The library can be sorted by reviews or by price/hour ratio.

The system shows basic information on each game: name, time to beat, reviews and steam price. The user can also add notes and their own rating to the games.

All the information is collected using APIs from Steam and HowLongToBeat. The huge list of steam games is automatically saved and refreshed from API if it's too old. User libraries can also be locally saved and loaded from a JSON document.

## Build

- Anarchy, it's every man for himself

## Dependencies

- nlohmann/json: https://github.com/nlohmann/json (header only - included)
- CLIUtils/CLI11: https://github.com/CLIUtils/CLI11 (header only - included)
- jgaa/restc-cpp: https://github.com/jgaa/restc-cpp

## API Usage

```cpp
// Create a game finder
GameFinder fin = GameFinder("games.txt");

// Create a library and specify the path to file where the games will be saved
GameLibrary lib = GameLibrary("user_games.txt");

// Print the whole library
Printer::print(lib);

// Add some games to the library
lib.add_game(fin.find_game("Celeste"));
lib.add_game(fin.find_game("Rocket League"));
lib.add_game(fin.find_game("Factorio"));
lib.add_game(fin.find_game("Car Parking 2"));
lib.add_game(fin.find_game("//TODO: today"));
lib.add_game(fin.find_game("Nonexistent Game"));               // adding a nonexistent game
lib.add_game(fin.find_game("Cyberpunk 2077"), 50);             // adding a game with user rating
lib.add_game(fin.find_game("Terraria", "hail the moon lord")); // adding a game with user note

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
```

## CLI Usage

```
  _____                 __ __
 / ___/__ ___ _  ___   / // /__ ___ ____
/ (_ / _ `/  ' \/ -_) / _  / -_) _ `/ _ \
\___/\_,_/_/_/_/\__/ /_//_/\__/\_,_/ .__/
                                  /_/

Usage: ./gameheap [OPTIONS] SUBCOMMAND

Options:
  -h,--help                   Print this help message and exit

Subcommands:
  demo                        Run the demo
  create                      Create a new library
  add                         Add a game to the library
  remove                      Remove a game from the library
  update                      Update a game in the library
  print                       List all games in the library
  print-simple                List all games in the library in a simple table
  sort                        Sort the library
```

<details>
<summary>Create CLI</summary>

```
Create a new library

Usage: ./gameheap create [OPTIONS] [path]

Positionals:
  path TEXT REQUIRED          Path to file with user games

Options:
  -h,--help                   Print this help message and exit
```
</details>

<details>
<summary>Add CLI</summary>

```
Add a game to the library

Usage: ./gameheap add [OPTIONS] path game

Positionals:
  path TEXT:FILE REQUIRED           Path to file with user games
  game TEXT REQUIRED                Name of the game to add

Options:
  -h,--help                         Print this help message and exit
  -g,--games TEXT:FILE              Path to file with games
  -r,--rating INT:INT in [0 - 100]  User rating
  -n,--note TEXT                    User note
```
</details>

<details>
<summary>Remove CLI</summary>

```
Remove a game from the library

Usage: ./gameheap remove [OPTIONS] [path] game

Positionals:
  path TEXT:FILE REQUIRED     Path to file with user games
  game TEXT REQUIRED          Name of the game to remove

Options:
  -h,--help                   Print this help message and exit
  -g,--games TEXT:FILE        Path to file with games
```
</details>

<details>
<summary>Update CLI</summary>

```
Update a game in the library

Usage: ./gameheap update [OPTIONS] [path] game

Positionals:
  path TEXT:FILE                    Path to file with user games
  game TEXT REQUIRED                Name of the game to update

Options:
  -h,--help                         Print this help message and exit
  -g,--games TEXT:FILE              Path to file with games
  -r,--rating INT:INT in [0 - 100]  User rating
  -n,--note TEXT                    User note
```
</details>

<details>
<summary>Print CLI</summary>

```
List all games in the library

Usage: ./gameheap print [OPTIONS] path

Positionals:
  path TEXT:FILE REQUIRED     Path to file with user games

Options:
  -h,--help                   Print this help message and exit
```
</details>

<details>
<summary>Print Simple CLI</summary>

```
List all games in the library in a simple table

Usage: ./gameheap print-simple [OPTIONS] path

Positionals:
  path TEXT:FILE REQUIRED     Path to file with user games

Options:
  -h,--help                   Print this help message and exit
```
</details>

<details>
<summary>Sort CLI</summary>

```
Sort the library

Usage: ./gameheap sort [OPTIONS] path

Positionals:
  path TEXT:FILE REQUIRED     Path to file with user games

Options:
  -h,--help                   Print this help message and exit
  -r,--rating                 Sort by average rating
  -m,--money-per-hour         Sort by money/hour ratio
```
</details>
