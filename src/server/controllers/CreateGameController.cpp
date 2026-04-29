
#include "CreateGameController.hpp"

void Controllers::CreateGameController::joinGame(const drogon::HttpRequestPtr& req,
                                    std::function<void (const drogon::HttpResponsePtr &)> &&callback)
{
    const auto json = req->getJsonObject();
    if (!json || !json->isMember("userId"))
    {
        auto response = drogon::HttpResponse::newHttpJsonResponse(
            Json::Value("missing userId")
        );
        response->setStatusCode(drogon::k400BadRequest);
        callback(response);
        return;
    }

    const auto userId = (*json)["userId"].asString();
    const auto playerJoined = game_.joinPlayer(std::stoi(userId));
    auto resp = drogon::HttpResponse::newHttpJsonResponse(
        playerJoined ? Json::Value("Added Value") : Json::Value("Failed to add player")
    );
    resp->setStatusCode(playerJoined ? drogon::k200OK : drogon::k400BadRequest);
    callback(resp);
}
