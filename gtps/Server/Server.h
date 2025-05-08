#ifndef SERVER_H
#define SERVER_H

#include "enet/include/enet/enet.h"
#include <thread>
#include <atomic>

class EnetServer
{
private:
    ENetHost* server = nullptr;
    std::thread serverThread;
    std::atomic<bool> isRunning{ false };
    const char* address = "0.0.0.0"; // any
    const int port = 17091;
    const size_t maxClients = 32;

    void run();

public:
    EnetServer();
    ~EnetServer();

    void start();
    void stop();
};

#endif
