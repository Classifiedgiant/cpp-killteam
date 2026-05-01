#ifndef KILLTEAM_SRC_SERVER_CONTROLLERS_GAMEWSCONTROLLERS_H_
#define KILLTEAM_SRC_SERVER_CONTROLLERS_GAMEWSCONTROLLERS_H_

#include <drogon/WebSocketController.h>
#include <drogon/HttpAppFramework.h>

#include <string>

namespace Controllers
{

class  GameWsController : public drogon::WebSocketController<GameWsController, false>
{
    public:
        void handleNewConnection(const drogon::HttpRequestPtr& req,
                                    const drogon::WebSocketConnectionPtr& conn) override;

        void handleConnectionClosed(const drogon::WebSocketConnectionPtr& conn) override;

        void handleNewMessage(const drogon::WebSocketConnectionPtr&, std::string&&, const drogon::WebSocketMessageType&) override;
        WS_PATH_LIST_BEGIN
        WS_PATH_LIST_END
};

}

#endif
