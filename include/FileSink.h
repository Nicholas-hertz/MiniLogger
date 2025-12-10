#pragma once
#include "Sink.h"
#include <fstream>
#include <mutex>
#include <string>

class FileSink : public Sink {
public:
    explicit FileSink(const std::string& filename);
    explicit FileSink(const std::string& filename, const int maxFileSizeInMb);
    ~FileSink() override;

    void write(const std::string& formattedMessage) override;

private:
    std::ofstream file_;
    std::mutex mutex_;
    bool rollFile_ { false };
    long long maxFileSize_ {};
    int fileCount_ {};
    std::string filename_ {};

    long long getFileSize(const std::string& filename);
    void openFile(const std::string& filename);
    void closeFile(); //uses currently open file
    void openFile(); //uses currently open file
    long long getFileSize(); //uses currently open file
};
