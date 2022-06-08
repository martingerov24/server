
#pragma once
#include "json.hpp"
#include "dep.h"

namespace jsonSend
{
    int getReqAndSize(
        const std::string& msg,
        HTTPReq& req
    ) {
        if (msg.empty())
        {
            printf("the recieve msg is empty!\n");
            return -1;
        }
        nlohmann::json json = nlohmann::json::parse(msg);
        if (json.contains("Post") == false){
            printf("cannot handle different request types in this funciton\n");
            return -1;
        }
        req = HTTPReq::Post;
        return json.value("Post", 0);
    }
}