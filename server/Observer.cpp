#include "TCPServer.h"


void EventLogger::update(const std::string &message) {
    // Implement logging logic here
    std::cout << "Subscribed events: " << message << std::endl;
}
