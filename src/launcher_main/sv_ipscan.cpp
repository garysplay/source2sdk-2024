#include "vbsp2.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

void ScanIPRange(const char* ipBase, int start, int end) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return;
    }

    for (int i = start; i <= end; ++i) {
        struct addrinfo* result = nullptr;
        char ipAddress[INET_ADDRSTRLEN];

        // Construct the IP address
        sprintf_s(ipAddress, "%s.%d", ipBase, i);

        // Resolve the IP address
        if (getaddrinfo(ipAddress, nullptr, nullptr, &result) == 0) {
            std::cout << "Host " << ipAddress << " is reachable." << std::endl;
            freeaddrinfo(result);
        }
    }

    WSACleanup();
}
