#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TCPServer
{
public:
    class Builder;

    void start() const;
    void handleClient(int clientSocket) const;

private:
    int port;
    int maxConnections;
    bool loggingEnabled;

    TCPServer(int p, int mc, bool le);
};

class TCPServer::Builder
{
private:
    int port;
    int maxConnections;
    bool loggingEnabled = false;

public:
    Builder &setPort(int p);
    Builder &setMaxConnections(int mc);
    Builder &enableLogging(bool le);
    TCPServer build() const;
};

#endif
