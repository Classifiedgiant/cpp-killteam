#include <catch2/catch_test_macros.hpp>

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <json/value.h>

#include "CreateGameController.hpp"
#include "Game.hpp"

static drogon::HttpResponsePtr callJoinGame(Controllers::CreateGameController& sut,
                                             drogon::HttpRequestPtr req)
{
    drogon::HttpResponsePtr captured;
    sut.joinGame(req, [&](const drogon::HttpResponsePtr& resp) {
        captured = resp;
    });
    return captured;
}

TEST_CASE("joinGame returns 400 when userId is missing")
{
    Game::Game game;
    Controllers::CreateGameController sut{game};

    auto req = drogon::HttpRequest::newHttpRequest();

    auto resp = callJoinGame(sut, req);

    REQUIRE(resp != nullptr);
    CHECK(resp->getStatusCode() == drogon::k400BadRequest);
}

TEST_CASE("joinGame returns 400 when JSON body is invalid")
{
    Game::Game game;
    Controllers::CreateGameController sut{game};

    auto req = drogon::HttpRequest::newHttpRequest();
    req->setContentTypeCode(drogon::CT_APPLICATION_JSON);
    req->setBody("not valid json");

    auto resp = callJoinGame(sut, req);

    REQUIRE(resp != nullptr);
    CHECK(resp->getStatusCode() == drogon::k400BadRequest);
}

TEST_CASE("joinGame returns 200, gameId, wsToken, playerPosition on success")
{
    Game::Game game;
    Controllers::CreateGameController sut{game};

    Json::Value body;
    body["userId"] = "1";
    auto req = drogon::HttpRequest::newHttpJsonRequest(body);

    auto resp = callJoinGame(sut, req);

    REQUIRE(resp != nullptr);
    CHECK(resp->getStatusCode() == drogon::k200OK);
    const auto json = resp->getJsonObject();
    REQUIRE(json != nullptr);
    CHECK(json->isMember("gameId"));
    CHECK(json->isMember("wsToken"));
    CHECK(json->isMember("playerPosition"));
    CHECK((*json)["playerPosition"].asInt() == 1);
}

TEST_CASE("joinGame returns 400 when game rejects player")
{
    Game::Game game;
    game.JoinPlayer(1, "abc", "def");
    game.JoinPlayer(2, "ghi", "jkl");

    Controllers::CreateGameController sut{game};

    Json::Value body;
    body["userId"] = "3";
    auto req = drogon::HttpRequest::newHttpJsonRequest(body);

    auto resp = callJoinGame(sut, req);

    REQUIRE(resp != nullptr);
    CHECK(resp->getStatusCode() == drogon::k400BadRequest);
}

TEST_CASE("joinGame returns 200 when same player attempts to join more than once")
{
    Game::Game game;
    Controllers::CreateGameController sut{game};

    Json::Value body;
    body["userId"] = "1";
    auto req = drogon::HttpRequest::newHttpJsonRequest(body);

    CHECK(callJoinGame(sut, req)->getStatusCode() == drogon::k200OK);
    CHECK(callJoinGame(sut, req)->getStatusCode() == drogon::k200OK);

    // player position
    body["userId"] = "2";
    req = drogon::HttpRequest::newHttpJsonRequest(body);
    CHECK(callJoinGame(sut, req)->getStatusCode() == drogon::k200OK);
    CHECK(callJoinGame(sut, req)->getStatusCode() == drogon::k200OK);
}

TEST_CASE("joinGame returns the same gameId, wsToken when called by the same user multiple times")
{
    Game::Game game;
    Controllers::CreateGameController sut{game};

    Json::Value body;
    body["userId"] = "1";
    auto req = drogon::HttpRequest::newHttpJsonRequest(body);

    const auto resp = callJoinGame(sut, req);

    REQUIRE(resp != nullptr);
    CHECK(resp->getStatusCode() == drogon::k200OK);
    auto json = resp->getJsonObject();
    REQUIRE(json != nullptr);
    CHECK(json->isMember("gameId"));
    CHECK(json->isMember("wsToken"));

    const auto prevGameId = (*json)["gameId"].asString();
    const auto prevWsToken = (*json)["wsToken"].asString();

    // second call
    json = callJoinGame(sut, req)->getJsonObject();
    CHECK((*json)["gameId"].asString() == prevGameId);
    CHECK((*json)["wsToken"].asString() == prevWsToken);
}
