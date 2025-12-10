#include "Logger.h"

Logger::Logger() : minLogLevel_(LogLevel::DEBUG) {}

void Logger::log(LogLevel level, const std::string& message) {
    if (level < minLogLevel_) return;

    const std::string formatted = formatter_.format(level, message);

    for (auto& sink : sinks_) {
        sink->write(formatted);
    }
}

void Logger::debug(const std::string& message) { log(LogLevel::DEBUG, message); }
void Logger::info(const std::string& message)  { log(LogLevel::INFO, message); }
void Logger::warn(const std::string& message)  { log(LogLevel::WARN, message); }
void Logger::error(const std::string& message) { log(LogLevel::ERROR, message); }

void Logger::addSink(std::unique_ptr<Sink> sink) {
    sinks_.push_back(std::move(sink));
}

void Logger::setLogLevel(LogLevel level) {
    minLogLevel_ = level;
}
