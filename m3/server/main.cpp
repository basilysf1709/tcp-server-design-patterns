#include "TCPServer.h"

int main()
{
    // Create the TCPServer instance using the Builder pattern
    TCPServer server = TCPServer::Builder()
                           .setPort(8080)
                           .setMaxConnections(100)
                           .enableLogging(true)
                           .build();

    // Decorate the TCPServer with the SecurityServerDecorator
    // Decorator Pattern
    SecurityServerDecorator secureServer(&server);

    // Observer Pattern & Singleton Pattern
    EventLogger logger;

    // Observer attached
    server.attach(&logger);

    // Start the server
    secureServer.start();

    // Observer detached
    server.detach(&logger);

    // When main exits, the TCPServer instance (server) will be automatically destroyed.
    return 0;
}
