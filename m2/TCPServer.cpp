#include "TCPServer.h"

void TCPServer::start() const
{
    std::cout << "Starting server at port: " << port
              << "\nwith max " << maxConnections << " connections"
              << (loggingEnabled ? "\nLogging is enabled" : "\nLogging is disabled.")
              << std::endl;

    // Creating Socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        std::cerr << "Socket creation failed." << std::endl;
        return;
    }

    // Bind socket to the IP / port
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed." << std::endl;
        return;
    }

    // Listen for incoming connections
    if (listen(server_fd, maxConnections) < 0)
    {
        std::cerr << "Listen failed." << std::endl;
        return;
    }

    // Accept incoming connection
    int addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket < 0)
    {
        std::cerr << "Accept failed." << std::endl;
        return;
    }

    close(new_socket);
    close(server_fd);
}

TCPServer::TCPServer(int p, int mc, bool le)
    : port(p), maxConnections(mc), loggingEnabled(le) {}

TCPServer::Builder &TCPServer::Builder::setPort(int p)
{
    port = p;
    return *this;
}

TCPServer::Builder &TCPServer::Builder::setMaxConnections(int mc)
{
    maxConnections = mc;
    return *this;
}

TCPServer::Builder &TCPServer::Builder::enableLogging(bool le)
{
    loggingEnabled = le;
    return *this;
}

TCPServer TCPServer::Builder::build() const
{
    return TCPServer(port, maxConnections, loggingEnabled);
}
