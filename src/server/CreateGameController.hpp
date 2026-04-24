
#ifndef KILLTEAM_SRC_SERVER_CREATEGAMECONTROLLER_H
#define KILLTEAM_SRC_SERVER_CREATEGAMECONTROLLER_H

#include <drogon/HttpSimpleController.h>

#include "Game.hpp"

namespace Controllers
{

class CreateGameController : public drogon::HttpSimpleController<CreateGameController, false>
{
    Game::Game game_;
public:

    CreateGameController(Game::Game& game) : game_(game) {}

    void asyncHandleHttpRequest(const drogon::HttpRequestPtr& req,
        std::function<void (const drogon::HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_LIST_END
};
}

#endif