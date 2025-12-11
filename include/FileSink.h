#pragma once
#include "Sink.h"
#include <fstream>
#include <mutex>
#include <string>

class FileSink : public Sink {
public:
    explicit FileSink(const std::string& filename);
    explicit FileSink(const std::string& filename, 
        int maxFileSizeInMb = 0,
        bool appendDateTimeToFilename = false);
    ~FileSink() override;

    void write(const std::string& formattedMessage) override;

private:
    std::ofstream file_;
    std::mutex mutex_;
    std::string filename_ {};
    bool rollFile_ { false };
    long long maxFileSize_ {};
    int fileCount_ {};
    bool appendDateTimeToFilename_ { false };

    void closeFile(); //uses currently open file
    void openFile(); //uses currently open file
    long long getFileSize(); //uses currently open file
    std::string generateFileName() const;  // private helper
};
