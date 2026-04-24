
#include "CreateGameController.hpp"

void Controllers::CreateGameController::asyncHandleHttpRequest(const drogon::HttpRequestPtr& req,
                                      std::function<void (const drogon::HttpResponsePtr &)> &&callback)
{
    Json::Value ret;
    ret["Lockie"] = "Tom";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
    std::cout << "Here we go" <<std::endl;

}
