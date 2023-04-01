#pragma once

#include <iostream>
#include <restc-cpp/restc-cpp.h>
#include <restc-cpp/RequestBuilder.h>
#include <unordered_map>
#include <fstream>

class SteamAPI
{
public:
    SteamAPI() = default;
    ~SteamAPI() = default;

    static int get(std::string url, std::unordered_map<std::string, std::string> arguments, std::string& response);

    static int get_games(std::string& response);
    static int get_game(std::string& response, std::string appid);

    void read_key(std::string filename);
};
