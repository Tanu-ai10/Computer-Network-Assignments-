
#include <iostream>
#include <winsock2.h>
using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET serverSocket;
    sockaddr_in serverAddr, clientAddr;
    char buffer[1024];
    int clientLen = sizeof(clientAddr);

    WSAStartup(MAKEWORD(2, 2), &wsa);

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr,
         sizeof(serverAddr));

    cout << "UDP Server waiting for message..." << endl;

    int bytes = recvfrom(serverSocket, buffer,
        sizeof(buffer) - 1, 0,
        (sockaddr*)&clientAddr, &clientLen);

    if (bytes != SOCKET_ERROR) {
        buffer[bytes] = '\0';
        cout << "Client says: " << buffer << endl;

        const char* reply = "Hello from UDP Server!";
        sendto(serverSocket, reply, strlen(reply), 0,
            (sockaddr*)&clientAddr, clientLen);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
