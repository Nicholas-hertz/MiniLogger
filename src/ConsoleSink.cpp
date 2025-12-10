#include "ConsoleSink.h"
#include <stdexcept>
#include <iostream>

ConsoleSink::ConsoleSink(std::ostream& os) : output_(os) {
    
}

ConsoleSink::~ConsoleSink() {
    
}

void ConsoleSink::write(const std::string& formattedMessage) {
    std::lock_guard<std::mutex> lock(mutex_);
    output_ << formattedMessage << std::endl;
}
