#include "Server.h"
#include <iostream>

EnetServer::EnetServer()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "Failed to initialize ENet." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::cout << "ENet initialized." << std::endl;
}

EnetServer::~EnetServer()
{
    stop();
    enet_deinitialize();
    std::cout << "ENet deinitialized." << std::endl;
}

void EnetServer::start()
{
    if (isRunning) return;

    ENetAddress addr;
    enet_address_set_host(&addr, address);
    addr.port = port;

    server = enet_host_create(&addr, maxClients, 2, 0, 0);
    if (!server)
    {
        std::cerr << "Failed to create ENet server host." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    isRunning = true;
    serverThread = std::thread(&EnetServer::run, this);
    std::cout << "Server started on " << address << ":" << port << std::endl;
}

void EnetServer::stop()
{
    if (!isRunning) return;

    isRunning = false;
    if (serverThread.joinable())
        serverThread.join();

    enet_host_destroy(server);
    server = nullptr;

    std::cout << "Server stopped." << std::endl;
}

void EnetServer::run()
{
    ENetEvent event;
    while (isRunning)
    {
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Client connected." << std::endl;
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "Packet received." << std::endl;
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Client disconnected." << std::endl;
                break;

            default:
                std::cout << "Unknown type." << std::endl;
                break;
            }
        }
    }
}
