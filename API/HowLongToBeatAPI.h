#pragma once

#include <iostream>
#include <restc-cpp/restc-cpp.h>
#include <restc-cpp/RequestBuilder.h>
#include <unordered_map>
#include "json.hpp"

class HowLongToBeatAPI
{
public:
    HowLongToBeatAPI() = default;
    ~HowLongToBeatAPI() = default;

    static int get(std::string url, std::string data, std::string& response);

    static int get_game(std::string& response, std::string name);
};
