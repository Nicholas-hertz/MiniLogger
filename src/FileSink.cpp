#include "FileSink.h"
#include <filesystem>
#include <stdexcept>

FileSink::FileSink(const std::string& filename)
    :  filename_(filename), maxFileSize_(0), fileCount_(0), appendDateTimeToFilename_(false)
{
    openFile();
}

FileSink::FileSink(const std::string& filename, int maxFileSizeInMb, bool appendDateTimeToFilename)
    : filename_(filename),
      maxFileSize_(static_cast<long long>(maxFileSizeInMb) * 1024LL * 1024LL), 
      fileCount_(0),
      appendDateTimeToFilename_(appendDateTimeToFilename)
{
    openFile();
}

FileSink::~FileSink() {
    std::lock_guard<std::mutex> lock(mutex_);
    if(file_.is_open()) {
        file_.close();
    }
}

void FileSink::write(const std::string& formattedMessage) {
    std::lock_guard<std::mutex> lock(mutex_);

    // Check file size if rotation is enabled
    if(maxFileSize_ > 0) {
        long long currFileSize = getFileSize();
        if(currFileSize >= maxFileSize_) {
            closeFile();
            fileCount_++;
            openFile(); // opens next rolling file
        }
    }

    file_ << formattedMessage << std::endl;
    file_.flush(); // ensure logs are written immediately
}

long long FileSink::getFileSize() {
    try {
        return std::filesystem::file_size(generateFileName());
    } catch (const std::filesystem::filesystem_error&) {
        return 0;
    }
}

void FileSink::openFile() {
    auto newFileName = generateFileName();
    file_.open(newFileName, std::ios::app);
    if(!file_.is_open()) {
        throw std::runtime_error("Failed to open log file: " + newFileName);
    }
}

void FileSink::closeFile() {
    if(file_.is_open()) {
        file_.close();
    }
}

std::string FileSink::generateFileName() const {
    std::string filename {};

    if(appendDateTimeToFilename_) {
        auto nowTimeStamp = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(nowTimeStamp);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d");
        filename += oss.str() + "_";
    }

    filename += filename_;

    if(fileCount_ > 0) {
        filename += "." + std::to_string(fileCount_);
    }

    return filename;
}
