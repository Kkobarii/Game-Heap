#include "HowLongToBeatAPI.h"

using namespace restc_cpp;

int HowLongToBeatAPI::get(std::string url, std::string data, std::string& response)
{
    std::cout << "HowLongToBeatAPI::get() called with url: " << url;
    std::cout << " and data: " << data << std::endl;

    int responseCode = 0;

    auto rest_client = RestClient::Create();
    rest_client->Process
    ([=, &response, &responseCode]
        (Context& ctx)
        {
        RequestBuilder builder(ctx);
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
    std::string data = R"({"searchTerms":[")" + name + R"("],"size":1})";

    return get(url, data, response);
}
