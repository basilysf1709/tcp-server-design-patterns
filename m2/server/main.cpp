#include "TCPServer.h"

int main() {
    TCPServer server = TCPServer::Builder()
                           .setPort(8080)
                           .setMaxConnections(100)
                           .enableLogging(true)
                           .build();

    server.start();
    return 0;
}
