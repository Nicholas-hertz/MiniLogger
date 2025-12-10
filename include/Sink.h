#pragma once
#include <string>

/// Abstract base class for log sinks
class Sink {
public:
    virtual ~Sink() = default;

    /// Write a formatted message to the sink
    virtual void write(const std::string& formattedMessage) = 0;
};
