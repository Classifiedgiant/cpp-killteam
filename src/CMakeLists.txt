find_package(Drogon CONFIG REQUIRED)

add_executable(KillteamServer main.cpp)

target_link_libraries(KillteamServer PRIVATE Drogon::Drogon)