#pragma once

#include <iostream>
#include <optional>
#include "json.hpp"

struct Price {
    int amount;
    std::string currency;
    std::string formatted;
};

struct SteamAttributes {
    int steam_appid;
    std::optional<int> rating;
    Price price;
};

struct HowLongToBeatAttributes {
    int howlongtobeat_appid;
    long completion_main;
    long completion_plus;
    long completion_100;
    std::optional<int> rating;
};

class Game {
private:
    std::string name;
    int priority = 0;

    std::optional<SteamAttributes> steam_attributes;
    std::optional<HowLongToBeatAttributes> howlongtobeat_attributes;

    std::optional<int> user_rating;

    bool archived = false;

    void calculate_priority();

public:
    Game(std::string name, std::optional<SteamAttributes> steam_attributes, std::optional<HowLongToBeatAttributes> howlongtobeat_attributes, std::optional<int> user_rating, bool archived);
    explicit Game(std::string game_string);

    std::string to_json();
    friend std::ostream& operator<<(std::ostream& ostr, const Game& game);

    void set_user_rating(int rating);
    int get_steam_id();

    std::string get_name() { return name; }
    std::optional<SteamAttributes> get_steam_attributes() { return steam_attributes; }
    std::optional<HowLongToBeatAttributes> get_howlongtobeat_attributes() { return howlongtobeat_attributes; }
    std::optional<int> get_user_rating() { return user_rating; }
    int get_priority() { return priority; }
    bool is_archived() { return archived; }

    void print_simple()
    {
        std::cout << static_cast<double>(priority)/100 << ": " << (static_cast<double>(priority)/100 < 10 ? " " : "");
        std::cout << "\t" << name << std::endl;
    }
};