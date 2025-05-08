#include <iostream>
#include "Server/Server.h"
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    EnetServer server;
    server.start();

    std::cout << "Press anything for stopping" << std::endl;
    std::cin.get();

    server.stop();
    return 0;
}