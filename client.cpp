#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int PORT_NUMBER = 12345; // Change to your desired port number
const char* SERVER_IP = "127.0.0.1"; // Change to the server's IP address

int main() {
    // Create a socket (Client)
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        return -1;
    }

    // Connect to the server (Client)
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT_NUMBER);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error connecting to server");
        return -1;
    }

    std::cout << "Connected to the server" << std::endl;

    // Send Data (Client)
    const char* message = "Hello, Server!";
    send(clientSocket, message, strlen(message), 0);

    // Receive Data (Client)
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

    if (bytesRead <= 0) {
        perror("Error receiving data");
        return -1;
    }

    std::cout << "Server says: " << buffer << std::endl;

    // Close Socket (Client)
    close(clientSocket);

    return 0;
}
