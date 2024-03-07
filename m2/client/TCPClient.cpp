#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    // Server's IP and port
    const char* server_ip = "127.0.0.1"; // Assuming the server is running on localhost
    const int server_port = 8080;        // Ensure this matches the server's listening port

    // Create a socket (IPv4, TCP)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Could not create socket" << endl;
        return -1;
    }

    // Define the server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);
    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
        cerr << "Invalid address / Address not supported" << endl;
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        cerr << "Connection failed" << endl;
        return -1;
    }
    cout << "Connected to server." << endl;

    string input;
    while (true) {
        cout << "Enter message to send (type 'exit' to quit): ";
        getline(cin, input);

        if (input == "exit") {
            break;
        }

        send(sock, input.c_str(), input.size(), 0);
        cout << "Message sent: " << input << endl;

        // Receive a response from the server (if the server sends a response)
        char buffer[1024] = {0};
        read(sock, buffer, 1024);
        cout << "Message received from server: " << buffer << endl;
    }


    // Close the socket
    close(sock);

    return 0;
}
