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
    std::optional<std::string> description;

    std::optional<SteamAttributes> steam_attributes;
    std::optional<HowLongToBeatAttributes> howlongtobeat_attributes;

    std::optional<int> user_rating;

    bool archived = false;

public:
    Game(std::string name,
         std::optional<SteamAttributes> steam_attributes,
         std::optional<HowLongToBeatAttributes> howlongtobeat_attributes,
         std::optional<int> user_rating, bool archived, std::optional<std::string> description = std::nullopt);
    explicit Game(std::string game_string);

    std::string to_json();
    friend std::ostream& operator<<(std::ostream& ostr, const Game& game);

    void set_user_rating(int rating);
    void set_description(std::string description) { this->description = description; }
    void set_archived(bool archived) { this->archived = archived; }
    int get_steam_id();

    std::string get_name() { return name; }
    std::optional<SteamAttributes> get_steam_attributes() { return steam_attributes; }
    std::optional<HowLongToBeatAttributes> get_howlongtobeat_attributes() { return howlongtobeat_attributes; }
    std::optional<int> get_user_rating() { return user_rating; }
    std::optional<std::string> get_description() { return description; }
    bool is_archived() { return archived; }

    void print_simple()
    {
        std::cout << "\t" << name << std::endl;
    }
};