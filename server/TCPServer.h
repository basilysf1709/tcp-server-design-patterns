#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>
#include <vector>

/**
 * @brief Interface for server implementations.
 * Provides abstract methods to start the server and handle client connections.
 * @author Basil Yusuf
 */
class IServer
{
public:
    /**
     * @brief start function
     * @return void
     */
    virtual void start() const = 0;
    /**
     * @brief Handles Client Connection
     * @param clientSocket Client Socket Number
     * @return void
     */
    virtual void handleClient(int clientSocket) const = 0;
    /**
     * @brief Empty Server Destructor
     * @return
     */
    virtual ~IServer() {}
};

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void update(const std::string &message) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {}
    virtual void attach(IObserver *observer) = 0;
    virtual void detach(IObserver *observer) = 0;
    virtual void notify(const std::string &message) const = 0;
};

class EventLogger : public IObserver {
public:
    virtual ~EventLogger() override {} 
    void update(const std::string &message) override;
};

/**
 * @brief TCP Server Class
 */
class TCPServer : public IServer, public ISubject
{
public:
    /**
     * @brief Builder Class
     */
    class Builder;

    /**
     * @brief Starts the TCP server.
     * Initializes server socket and listens for incoming client connections.
     */
    virtual void start() const;
    /**
     * @brief Handles a client connection for the TCP server.
     * Defines the interaction with the connected TCP client.
     * @param clientSocket The socket descriptor for the connected client.
     */
    virtual void handleClient(int clientSocket) const;
    // Subject methods
    void attach(IObserver *observer) override;
    void detach(IObserver *observer) override;
    void notify(const std::string &message) const override;

private:
    int port;
    int maxConnections;
    bool loggingEnabled;

    /**
     * @brief Constructor for TCPServer.
     * @param p Port number for the server.
     * @param mc Maximum number of concurrent connections.
     * @param le Flag to enable or disable logging.
     */
    TCPServer(int p, int mc, bool le);
    std::vector<IObserver *> observers;
};
/**
 * @brief Builder class for constructing TCPServer objects.
 * Enables the configuration and construction of TCPServer instances.
 */
class TCPServer::Builder
{
private:
    int port;            // Port number for the server
    int maxConnections;  // Maximum number of concurrent connections
    bool loggingEnabled; // Flag to enable or disable logging

public:
    Builder &setPort(int p);            // Sets the server port
    Builder &setMaxConnections(int mc); // Sets the maximum number of connections
    Builder &enableLogging(bool le);    // Enables or disables logging
    TCPServer build() const;            // Constructs the TCPServer with the configured settings
};

// Singleton Pattern
class Logger
{
public:
    /**
     * @brief Retrieves the singleton instance of Logger.
     * Ensures that only one Logger instance is created.
     * @return Reference to the singleton Logger instance.
     */
    static Logger &getInstance();

    /**
     * @brief Logs a message.
     * Outputs a message to the standard output or a log file.
     * @param message The message to be logged.
     */
    void logMessage(const std::string &message);

    Logger(const Logger &) = delete;            // Copy constructor is deleted
    Logger &operator=(const Logger &) = delete; // Assignment operator is deleted

private:
    /**
     * @brief Private constructor for Logger.
     * Part of the Singleton pattern to prevent multiple instances.
     */
    Logger();
};

/**
 * @brief Base decorator class for servers.
 * Allows additional behaviors to be added to servers dynamically.
 */
class ServerDecorator : public IServer
{
protected:
    IServer *wrappedServer;

public:
    /**
     * @brief Constructor for ServerDecorator.
     * Wraps an existing server instance to add new behaviors.
     * @param server Pointer to the server to be decorated.
     */
    ServerDecorator(IServer *server);
    /**
     * @brief Destructor for ServerDecorator.
     */
    virtual ~ServerDecorator() {}
    virtual void start() const override;                        // Starts the decorated server
    virtual void handleClient(int clientSocket) const override; // Handles client for the decorated server
};

/**
 * @brief Decorator class for adding security features to a server.
 * Extends ServerDecorator to add security measures like authentication.
 */
class SecurityServerDecorator : public ServerDecorator
{
public:
    /**
     * @brief Constructor for SecurityServerDecorator.
     * Initializes a new instance of SecurityServerDecorator, wrapping an existing server.
     * @param decorator The server instance to be decorated with additional security features.
     */
    SecurityServerDecorator(IServer *decorator);

    /**
     * @brief Starts the decorated server with additional security features.
     * Overrides the start method to include security initialization procedures.
     */
    void start() const override;

    /**
     * @brief Handles client connections with added security.
     * Overrides the handleClient method to include security checks
     * such as authentication and encryption.
     * @param clientSocket The socket descriptor for the connected client.
     */
    void handleClient(int clientSocket) const override;
};



#endif