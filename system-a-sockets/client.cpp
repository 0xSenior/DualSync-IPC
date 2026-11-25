#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "common.h"

using namespace std;


int connect_to_server(const char* server_ip, int port) {
    // Create client socket (IPv4, TCP)
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        cerr << "[Client] Failed to create socket" << endl;
        exit(1);
    }
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

   if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        cerr << "[Client] Invalid address" << endl;
        exit(1);
    }

        if (connect(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "[Client] Connection failed" << endl;
        exit(1);
    }

    cout << "[Client] Connected to server successfully" << endl;
    return sock_fd;
}




void send_message(int sock_fd, const string& msg) {
    send(sock_fd, msg.c_str(), msg.length(), 0);
    cout << "[Client Sent] : " << msg << endl;
}

int main() {
    cout << "--- Chat Client Starting ---" << endl;

    int sock_fd = connect_to_server("127.0.0.1", PORT);

    
    string message = "Hello from Client";
    send_message(sock_fd, message);

    
    close(sock_fd);

    cout << "--- Client end ---" << endl;
    return 0;
}

