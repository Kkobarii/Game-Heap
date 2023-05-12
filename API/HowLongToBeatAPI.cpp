#include "HowLongToBeatAPI.h"

using json = nlohmann::json;

int HowLongToBeatAPI::get(std::string url, std::string data, std::string& response)
{
    std::string message = "HowLongToBeatAPI::get() called with url: " + url + " and data: " + data;
    Logger::log(message, 2);

    int responseCode = 0;

    auto rest_client = restc_cpp::RestClient::Create();
    rest_client->Process
    ([=, &response, &responseCode]
        (restc_cpp::Context& ctx)
        {
        restc_cpp::RequestBuilder builder(ctx);
        builder.Post(url);
        builder.Header("User-Agent", "foobar/2000");
        builder.Header("content-type", "application/json");
        builder.Header("origin", "https://howlongtobeat.com");
        builder.Header("referer", "https://howlongtobeat.com/");
        builder.Data(data);

        auto reply = builder.Execute();

        responseCode = reply->GetResponseCode();
        response = reply->GetBodyAsString();
    });

    return responseCode;
}

int HowLongToBeatAPI::get_game(std::string& response, std::string name)
{
    std::string url = "https://howlongtobeat.com/api/search";
    json json = {
        {"searchTerms", {name}},
        {"size", 1}
    };
    std::string data = json.dump();

    return get(url, data, response);
}
