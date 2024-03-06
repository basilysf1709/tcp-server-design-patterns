#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

class TCPServer
{
public:
    class Builder;

    void start() const;

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
