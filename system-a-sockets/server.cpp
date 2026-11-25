#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "common.h"
using namespace std;



int start_server(int port) {
    
    // grab a fresh TCP socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        cerr << "Failed to create socket" << endl;
        exit(1);
    }

    // setup server address IP & Port
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port); // fix intgers reverse gpu & network
    address.sin_addr.s_addr = INADDR_ANY;

    // bind socket to port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        cerr << "[Server] Port " << port << " is already in use" << endl;
        exit(1);
    }

    // listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        cerr << "[Server] Failed to listen" << endl;
        exit(1);
    }

    cout << "[Server] Listening on port " << port << "..." << endl;
    return server_fd;
}


// Wait and accept incoming client connection
int accept_client(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);
    
    // Program pauses here until a client connects
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);
    if (client_fd < 0) {
        cerr << "[Server] Failed to accept client" << endl;
        exit(1);
    }
    cout << "[Server] Client connected successfully" << endl;
    return client_fd;
}

// Read incoming message and print it out
void handle_client(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    while (true) {
        // Clear buffer before read
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        // error occurred
        if (bytes_read <= 0) {
            cout << "[Server] Client disconnected" << endl;
            break;
        }
        cout << "[Server Received] : " << buffer << endl;
    }
    
    close(client_fd);
}

int main() {

    int server_fd = start_server(PORT);
    int client_fd = accept_client(server_fd);
    handle_client(client_fd);

    close(server_fd);
    return 0;
}


