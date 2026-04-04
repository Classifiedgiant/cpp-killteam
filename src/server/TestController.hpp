#ifndef KILLTEAM_SRC_SERVER_TESTCONTROLLER_H
#define KILLTEAM_SRC_SERVER_TESTCONTROLLER_H

#include <drogon/HttpSimpleController.h>

namespace Controllers
{

class TestController : public drogon::HttpSimpleController<TestController>
{
public:
    void asyncHandleHttpRequest(const drogon::HttpRequestPtr& req, std::function<void (const drogon::HttpResponsePtr &)> &&callback) override;
    PATH_LIST_BEGIN
    PATH_ADD("/test", drogon::Get);
    PATH_LIST_END
};
}

#endif
