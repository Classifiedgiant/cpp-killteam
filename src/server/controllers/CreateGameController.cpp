#include "CreateGameController.hpp"

#include "RandomGenerator.hpp"
#include "ControllerHelper.hpp"

void Controllers::CreateGameController::joinGame(const drogon::HttpRequestPtr& req,
                                    std::function<void (const drogon::HttpResponsePtr &)> &&callback)
{
    const auto json = req->getJsonObject();
    if (!json || !json->isMember("userId"))
    {
        Json::Value errorJson{};
        errorJson["error"] = "missing UserId";
        callback(Util::Create400JsonResponse(errorJson));
        return;
    }

    const auto userId = std::stoi((*json)["userId"].asString());
    if (game_.IsPlayerInGame(userId) || game_.IsFull())
    {
        Json::Value errorJson{};
        errorJson["error"] = "Failed to add player";
        callback(Util::Create400JsonResponse(errorJson));
    }
    else
    {
        // send a websocket connection for game related
        Json::Value returnJson{};


        const auto gameId = Util::GenerateAlphaNumericString(5);
        const auto wsToken = Util::GenerateAlphaNumericString(10);
        game_.joinPlayer(userId, wsToken, gameId);

        game_.SetGameId(gameId);
        returnJson["gameId"] =  game_.GetGameId();
        returnJson["wsToken"] = wsToken;
        returnJson["playerPosition"] = game_.IsFull() ? 2 : 1 ;
        const auto resp = drogon::HttpResponse::newHttpJsonResponse(returnJson);
        callback(resp);
    }
}
