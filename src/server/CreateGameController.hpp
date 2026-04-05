
#ifndef KILLTEAM_SRC_SERVER_CREATEGAMECONTROLLER_H
#define KILLTEAM_SRC_SERVER_CREATEGAMECONTROLLER_H

#include <drogon/HttpSimpleController.h>

namespace Controllers
{

class CreateGameController : public drogon::HttpSimpleController<CreateGameController>
{
public:
    void asyncHandleHttpRequest(const drogon::HttpRequestPtr& req,
        std::function<void (const drogon::HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/game", drogon::Post);
    PATH_LIST_END
};
}

#endif