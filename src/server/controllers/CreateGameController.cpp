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
    if (!game_.IsPlayerInGame(userId) && game_.IsFull())
    {
        Json::Value errorJson{};
        errorJson["error"] = "Failed to add player";
        callback(Util::Create400JsonResponse(errorJson));
    }
    else if (game_.IsPlayerInGame(userId))
    {
        // resend players connection details
        Json::Value returnJson{};
        returnJson["gameId"] =  game_.GetGameId();
        returnJson["wsToken"] = game_.GetPlayer(userId)->GetConnectionToken();
        const auto resp = drogon::HttpResponse::newHttpJsonResponse(returnJson);
        callback(resp);
    }
    else
    {
        // send a websocket connection for game related

        const auto gameId = Util::GenerateAlphaNumericString(5);
        const auto wsToken = Util::GenerateAlphaNumericString(10);
        game_.JoinPlayer(userId, wsToken, gameId);
        game_.SetGameId(gameId);

        Json::Value returnJson{};
        returnJson["gameId"] = gameId;
        returnJson["wsToken"] = wsToken;
        returnJson["playerPosition"] = game_.IsFull() ? 2 : 1;
        const auto resp = drogon::HttpResponse::newHttpJsonResponse(returnJson);
        callback(resp);
    }
}
