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

TEST_CASE("joinGame returns 200 and a gameSessionId on success")
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
    CHECK(json->isMember("gameSessionId"));
}

TEST_CASE("joinGame returns 400 when game rejects player")
{
    Game::Game game;
    REQUIRE(game.joinPlayer(1));
    REQUIRE(game.joinPlayer(2));

    Controllers::CreateGameController sut{game};

    Json::Value body;
    body["userId"] = "3";
    auto req = drogon::HttpRequest::newHttpJsonRequest(body);

    auto resp = callJoinGame(sut, req);

    REQUIRE(resp != nullptr);
    CHECK(resp->getStatusCode() == drogon::k400BadRequest);
}
