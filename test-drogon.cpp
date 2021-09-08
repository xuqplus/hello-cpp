#include <iostream>
#include <drogon/drogon.h>

using namespace drogon;

int main()
{
    std::cout << "start web server .." << std::endl;
    app()
        .setLogPath("./")
        .setLogLevel(trantor::Logger::kWarn)
        .addListener("0.0.0.0", 8080)
        .setThreadNum(16)
        // .enableRunAsDaemon()
        .registerHandler("/a?name={name}",
                         [](const HttpRequestPtr &req,
                            std::function<void(const HttpResponsePtr &)> &&callback,
                            const std::string &name)
                         {
                             Json::Value json;
                             json["result"] = "ok";
                             json["message"] = std::string("hello,") + name;
                             auto resp = HttpResponse::newHttpJsonResponse(json);
                             callback(resp);
                         },
                         {Get, "handler-name"})
        .run();
    return 0;
}
