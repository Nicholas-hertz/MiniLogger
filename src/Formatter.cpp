#include "Formatter.h"
#include <chrono>
#include <iomanip>
#include <sstream>

using std::string;
using std::time_t;

string Formatter::format(LogLevel level, const string& message) const {
    std::ostringstream oss;
    oss << "[" << getTimestamp() << "] "
        << "[" << logLevelToString(level) << "] "
        << message;
    return oss.str();
}

string Formatter::getTimestamp() const {
    auto nowTimeStamp = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(nowTimeStamp);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return oss.str();
}
