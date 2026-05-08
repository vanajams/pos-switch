#include "utils/logger.h"

Logger::Logger(const std::string& logMsg)
    : logMessage(logMsg)
{
    std::cout << "[LOGGER INITIALIZED] "
              << "Message: " << logMessage
              << " | Length: " << logMessage.length()
              << std::endl;
}

void Logger::info(const std::string& message)
{
    std::cout << "[INFO] "
              << message
              << std::endl;
}

void Logger::error(const std::string& message)
{
    std::cerr << "[ERROR] "
              << message
              << std::endl;
}