#pragma once
#include "Sink.h"
#include <fstream>
#include <mutex>
#include <string>

class FileSink : public Sink {
public:
    explicit FileSink(const std::string& filename);
    ~FileSink() override;

    void write(const std::string& formattedMessage) override;

private:
    std::ofstream file_;
    std::mutex mutex_;
};
