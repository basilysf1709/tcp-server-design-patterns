#include "TCPServer.h"

/**
 * @brief Logger Constructor
 */
Logger::Logger() {}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::logMessage(const std::string& message) {
    std::cout << "Log: " << message << std::endl;
}
