#include <iostream>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

using namespace std;

int main() {

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Winsock initialization failed!" << endl;
        return 1;
    }
#endif

    // 1. Create TCP socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket ==
#ifdef _WIN32
        INVALID_SOCKET
#else
        -1
#endif
    ) {
        cout << "Socket creation failed!" << endl;
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    // Server address
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    // Server IP address
        // Use the Windows-compatible IPv4 conversion available with Winsock.
        serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        if (serverAddress.sin_addr.s_addr == INADDR_NONE) {
        cout << "Invalid server IP address!" << endl;
    #ifdef _WIN32
        closesocket(clientSocket);
        WSACleanup();
    #else
        close(clientSocket);
    #endif
        return 1;
        }

    // 2. Connect to server
    if (connect(
            clientSocket,
            (struct sockaddr*)&serverAddress,
            sizeof(serverAddress)) < 0) {

        cout << "Connection failed!" << endl;
    #ifdef _WIN32
        closesocket(clientSocket);
        WSACleanup();
    #else
        close(clientSocket);
    #endif
        return 1;
    }

    cout << "Connected to server!" << endl;

    // 3. Input message from user
    string message;

    cout << "Enter message: ";
    getline(cin, message);

    // 4. Send message to server
    send(
        clientSocket,
        message.c_str(),
        message.length(),
        0
    );

    // 5. Receive reply from server
    char buffer[1024] = {0};

    int bytesReceived = recv(
        clientSocket,
        buffer,
        sizeof(buffer) - 1,
        0
    );

    if (bytesReceived > 0) {

        buffer[bytesReceived] = '\0';

        // 6. Display server reply
        cout << "Server reply: "
             << buffer << endl;
    }

    // 7. Close client socket
#ifdef _WIN32
    closesocket(clientSocket);
    WSACleanup();
#else
    close(clientSocket);
#endif

    return 0;
}