#include "TestController.hpp"

void Controllers::TestController::asyncHandleHttpRequest(const drogon::HttpRequestPtr& req,
                                      std::function<void (const drogon::HttpResponsePtr &)> &&callback)
{
    Json::Value ret;
    ret["message"] = "Lockie here";
    auto resp = drogon::HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}
