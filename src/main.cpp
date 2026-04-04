#include <iostream>
#include <drogon/drogon.h>

int main()
{
    std::cout << "Starting the server...\n";
    drogon::app()
    .setLogPath("./")
    .setLogLevel(trantor::Logger::kWarn)
    .addListener("0.0.0.0", 1337)
    .setThreadNum(16)
    .run();

    return 0;
}
