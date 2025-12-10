#include "FileSink.h"
#include <stdexcept>

FileSink::FileSink(const std::string& filename) {
    file_.open(filename, std::ios::app);
    if (!file_.is_open()) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
}

FileSink::~FileSink() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileSink::write(const std::string& formattedMessage) {
    std::lock_guard<std::mutex> lock(mutex_);
    file_ << formattedMessage << std::endl;
}
