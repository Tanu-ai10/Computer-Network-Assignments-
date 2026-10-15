#include <iostream>
#include <cstring>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Winsock initialization failed!" << endl;
        return 1;
    }

    // 1. Create TCP socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == INVALID_SOCKET) {
        cout << "Socket creation failed!" << endl;
        WSACleanup();
        return 1;
    }

    // Server address
    sockaddr_in serverAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // 2. Bind socket to IP address and port
    if (bind(serverSocket,
             reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) == SOCKET_ERROR) {

        cout << "Bind failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // 3. Listen for client connection
    if (listen(serverSocket, 5) == SOCKET_ERROR) {
        cout << "Listen failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server is waiting for client..." << endl;

    // 4. Accept client connection
    sockaddr_in clientAddress;
    socklen_t clientSize = sizeof(clientAddress);

    SOCKET clientSocket = accept(
        serverSocket,
        reinterpret_cast<sockaddr*>(&clientAddress),
        &clientSize
    );

    if (clientSocket == INVALID_SOCKET) {
        cout << "Client connection failed!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    cout << "Client connected!" << endl;

    // 5. Receive message from client
    char buffer[1024] = {0};

    int bytesReceived = recv(
        clientSocket,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if (bytesReceived > 0) {

        buffer[bytesReceived] = '\0';

        // 6. Display received message
        cout << "Message from client: "
             << buffer << endl;

        // 7. Send reply to client
        string reply = "Hello from Server! Message received.";

        send(
            clientSocket,
            reply.c_str(),
            reply.length(),
            0
        );
    }

    // 8. Close client connection
    closesocket(clientSocket);

    // 9. Close server socket
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}