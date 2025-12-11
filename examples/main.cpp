#include "Logger.h"
#include "FileSink.h"
#include <memory>
#include <ConsoleSink.h>
#include <iostream>

void testLogs(Logger& logger){
    logger.info("Application started");
    logger.debug("Debug message here");
    logger.warn("Warning example");
    logger.error("Error example");
}


int main() {
    Logger logger;
    
    // Add a file sink
    logger.addSink(std::make_unique<FileSink>("app.log", 1, true));
    logger.addSink(std::make_unique<ConsoleSink>());

    // Test logging
    std::cout << "Starting 10000 iterations..." << std::endl;
    for(int i = 0; i < 10001; i++)
    {
        if(i % 1000 == 0) {
            std::cout << "Iteration: " << i << std::endl;
        }
        testLogs(logger);
    }
    std::cout << "Completed all iterations!" << std::endl;

    return 0;
}