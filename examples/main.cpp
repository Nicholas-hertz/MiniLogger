#include "Logger.h"
#include "FileSink.h"
#include <memory>
#include <ConsoleSink.h>

int main() {
    Logger logger;
    
    // Add a file sink
    logger.addSink(std::make_unique<FileSink>("app.log"));
    logger.addSink(std::make_unique<ConsoleSink>());

    // Test logging
    logger.info("Application started");
    logger.debug("Debug message here");
    logger.warn("Warning example");
    logger.error("Error example");

    return 0;
}
