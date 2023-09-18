#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT_NUMBER = 12345; // Change to your desired port number
const int BACKLOG = 5;
const char* SERVER_IP = "127.0.0.1"; // Change to the server's IP address

int main() {
    // Create a socket (Server)
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        return -1;
    }

    // Bind and Listen (Server)
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT_NUMBER);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error binding");
        return -1;
    }

    if (listen(serverSocket, BACKLOG) == -1) {
        perror("Error listening");
        return -1;
    }

    std::cout << "Server listening on port " << PORT_NUMBER << std::endl;

    // Accept Connections (Server)
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);

    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        perror("Error accepting client connection");
        return -1;
    }

    std::cout << "Client connected" << std::endl;

    // Receive and Send Data
    char buffer[1024];
    int bytesRead;

    while (true) {
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer

        // Receive data from the client
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            perror("Error receiving data");
            break;
        }

        std::cout << "Received: " << buffer << std::endl;

        // Send data back to the client (echo)
        send(clientSocket, buffer, strlen(buffer), 0);
    }

    // Close Sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
