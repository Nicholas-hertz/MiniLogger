#include "FileSink.h"
#include <filesystem>
#include <stdexcept>

FileSink::FileSink(const std::string& filename)
    : maxFileSize_(0), fileCount_(0), filename_(filename)
{
    openFile(filename_);
}

FileSink::FileSink(const std::string& filename, const int maxFileSizeInMb)
    : maxFileSize_(static_cast<long long>(maxFileSizeInMb) * 1024LL * 1024LL), 
      fileCount_(0), 
      filename_(filename)
{
    openFile(filename_);
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
            openFile(); // opens next rolling file
        }
    }

    file_ << formattedMessage << std::endl;
    file_.flush(); // ensure logs are written immediately
}

long long FileSink::getFileSize() {
    try {
        std::string fname = filename_;
        if(fileCount_ > 0) {
            fname = filename_ + "." + std::to_string(fileCount_);
        }
        return std::filesystem::file_size(fname);
    } catch (const std::filesystem::filesystem_error&) {
        return 0;
    }
}

void FileSink::openFile(const std::string& filename) {
    file_.open(filename, std::ios::app);
    if(!file_.is_open()) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
}

void FileSink::closeFile() {
    if(file_.is_open()) {
        file_.close();
    }
}

void FileSink::openFile() {
    fileCount_++; // increment rolling count
    std::string newFile = filename_;
    if(fileCount_ > 0) {
        newFile = filename_ + "." + std::to_string(fileCount_);
    }
    file_.open(newFile, std::ios::app);
    if(!file_.is_open()) {
        throw std::runtime_error("Failed to open log file: " + newFile);
    }
}

long long FileSink::getFileSize(const std::string& filename) {
    try {
        return std::filesystem::file_size(filename);
    } catch (const std::filesystem::filesystem_error&) {
        return 0;
    }
}
