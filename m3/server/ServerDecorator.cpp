// In ServerDecorator.cpp

#include "TCPServer.h"


ServerDecorator::ServerDecorator(ServerDecorator *server) : wrappedServer(server) {}

void ServerDecorator::start() const {
    if (wrappedServer) {
        wrappedServer->start();
    }
}

void ServerDecorator::handleClient(int clientSocket) const {
    if (wrappedServer) {
        wrappedServer->handleClient(clientSocket);
    }
}

SecurityServerDecorator::SecurityServerDecorator(ServerDecorator *decorator) : ServerDecorator(decorator) {}

void SecurityServerDecorator::start() const {
    std::cout << "Security: Server is starting with enhanced security measures." << std::endl;
    ServerDecorator::start();
}

void SecurityServerDecorator::handleClient(int clientSocket) const {
    std::cout << "Security: Securing client connection." << std::endl;
    ServerDecorator::handleClient(clientSocket);
}
