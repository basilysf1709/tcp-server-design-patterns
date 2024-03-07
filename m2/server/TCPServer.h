#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>


class IServer {
public:
    virtual void start() const = 0;
    virtual void handleClient(int clientSocket) const = 0;
    virtual ~IServer() {}
};
class TCPServer : public IServer
{
public:
    class Builder;

    virtual void start() const;
    virtual void handleClient(int clientSocket) const;

private:
    int port;
    int maxConnections;
    bool loggingEnabled;

    TCPServer(int p, int mc, bool le);
};

// Builder Pattern
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

// Singleton Pattern
class Logger {
public:
    static Logger& getInstance();
    void logMessage(const std::string& message);
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();
};

// Server Decorator Pattern
class ServerDecorator : public IServer {
protected:
    std::unique_ptr<ServerDecorator> wrappedServer;

public:
    ServerDecorator(ServerDecorator *server);
    virtual ~ServerDecorator() {}

    virtual void start() const override;
    virtual void handleClient(int clientSocket) const override;
};


class SecurityServerDecorator : public ServerDecorator {
public:
    SecurityServerDecorator(ServerDecorator *decorator);
    void start() const override;
    void handleClient(int clientSocket) const override;
};

#endif