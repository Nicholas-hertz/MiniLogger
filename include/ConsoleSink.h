#pragma once
#include "Sink.h"
#include <fstream>
#include <mutex>
#include <string>

class ConsoleSink : public Sink {
public:
    explicit ConsoleSink(std::ostream& os = std::cout);
    ~ConsoleSink() override;

    void write(const std::string& formattedMessage) override;

private:
    std::ostream& output_;
    std::mutex mutex_;
};
