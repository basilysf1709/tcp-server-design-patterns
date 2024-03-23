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
    SecurityServerDecorator secureServer(&server);

    // Start the server
    secureServer.start();

    // When main exits, the TCPServer instance (server) will be automatically destroyed.
    return 0;
}
