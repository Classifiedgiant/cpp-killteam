#ifndef KILLTEAM_SRC_UTIL_CONTROLLERHELPER_H
#define KILLTEAM_SRC_UTIL_CONTROLLERHELPER_H

#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>

namespace Util
{
    static drogon::HttpResponsePtr Create400JsonResponse(const Json::Value& json)
    {
        const auto response = drogon::HttpResponse::newHttpJsonResponse(json);
        response->setStatusCode(drogon::k400BadRequest);
        return response;
    }
}
#endif