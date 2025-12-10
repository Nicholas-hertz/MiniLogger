#pragma once
#include <string>

/// Defines the severity of a log message.
enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

/// Convert LogLevel enum to a string
inline std::string logLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}
