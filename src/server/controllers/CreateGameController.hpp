
#ifndef KILLTEAM_SRC_SERVER_CREATEGAMECONTROLLER_H
#define KILLTEAM_SRC_SERVER_CREATEGAMECONTROLLER_H

#include <drogon/HttpController.h>

#include "Game.hpp"

namespace Controllers
{

class CreateGameController : public drogon::HttpController<CreateGameController, false>
{
    Game::Game game_;
public:

    CreateGameController(Game::Game& game) : game_(game) {}

    void joinGame(const drogon::HttpRequestPtr& req,
        std::function<void (const drogon::HttpResponsePtr &)> &&callback);
    METHOD_LIST_BEGIN
    METHOD_LIST_END
};
}

#endif