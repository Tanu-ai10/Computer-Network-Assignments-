
#include <iostream>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024] = "Hello from UDP Client!";
    char reply[1024];
    int serverLen = sizeof(serverAddr);

    WSAStartup(MAKEWORD(2, 2), &wsa);

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(clientSocket, buffer, strlen(buffer), 0,
        (sockaddr*)&serverAddr, sizeof(serverAddr));

    int bytes = recvfrom(clientSocket, reply,
        sizeof(reply) - 1, 0,
        (sockaddr*)&serverAddr, &serverLen);

    if (bytes != SOCKET_ERROR) {
        reply[bytes] = '\0';
        cout << "Server reply: " << reply << endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
