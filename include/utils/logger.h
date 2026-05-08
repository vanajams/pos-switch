#pragma once

#include <iostream>
#include <string>

class Logger {

public:

    Logger(const std::string& logMsg);

    void info(const std::string& message);

    void error(const std::string& message);

private:

    std::string logMessage;

    int msgLength;
};