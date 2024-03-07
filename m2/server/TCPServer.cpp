#include "TCPServer.h"

void TCPServer::start() const
{
    Logger::getInstance().logMessage("Starting server at port: " + std::to_string(port) + "\nwith max " + std::to_string(maxConnections) + " connections" + (loggingEnabled ? "\nLogging is enabled" : "\nLogging is disabled."));

    // Creating Socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0)
    {
        Logger::getInstance().logMessage("Socket creation failed.");
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
        Logger::getInstance().logMessage("Bind failed.");
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
        Logger::getInstance().logMessage("Accept failed.");
        return;
    }

    handleClient(new_socket);

    close(new_socket);
    close(server_fd);
}

void TCPServer::handleClient(int clientSocket) const
{
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    while (true)
    {
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0)
        {
            Logger::getInstance().logMessage("Client disconnected.");
            break;
        }

        // bytesReceived += ": Server got your message";
        send(clientSocket, buffer, bytesReceived, 0);
        // Logging received message
        if (loggingEnabled)
        {
            std::cout << "Received message: " << buffer << std::endl;
        }
    }
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
