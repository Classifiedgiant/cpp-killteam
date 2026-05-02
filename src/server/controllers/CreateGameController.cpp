#include "CreateGameController.hpp"

#include "RandomGenerator.hpp"

void Controllers::CreateGameController::joinGame(const drogon::HttpRequestPtr& req,
                                    std::function<void (const drogon::HttpResponsePtr &)> &&callback)
{
    const auto json = req->getJsonObject();
    if (!json || !json->isMember("userId"))
    {
        Json::Value errorJson{};
        errorJson["error"] = "missing UserId";
        const auto response = drogon::HttpResponse::newHttpJsonResponse(errorJson);
        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    const auto userId = (*json)["userId"].asString();
    if (const auto playerJoined = game_.joinPlayer(std::stoi(userId)); !playerJoined)
    {
        Json::Value errorJson{};
        errorJson["error"] = "Failed to add player";
        const auto resp = drogon::HttpResponse::newHttpJsonResponse(errorJson);
        resp->setStatusCode(drogon::k400BadRequest);
        callback(resp);
    }
    else
    {
        // send a websocket connection for game related
        Json::Value returnJson{};
        returnJson["gameSessionId"] = Util::GenerateAlphaNumericString(5);
        const auto resp = drogon::HttpResponse::newHttpJsonResponse(returnJson);
        callback(resp);
    }
}
