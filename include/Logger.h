#pragma once
#include "Sink.h"
#include "Formatter.h"
#include "LogLevel.h"

#include <memory>
#include <vector>
#include <string>

class Logger {
public:
    Logger();
    ~Logger() = default;

    void log(LogLevel level, const std::string& message);

    // Convenience methods
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

    void addSink(std::unique_ptr<Sink> sink);

    void setLogLevel(LogLevel level);

private:
    std::vector<std::unique_ptr<Sink>> sinks_;
    Formatter formatter_;
    LogLevel minLogLevel_;
};
