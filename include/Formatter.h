#pragma once
#include "LogLevel.h"
#include <string>

class Formatter {
public:
    Formatter() = default;
    ~Formatter() = default;

    /// Format a log message with timestamp and level
    std::string format(LogLevel level, const std::string& message) const;

private:
    std::string getTimestamp() const;
};
