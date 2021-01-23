#pragma once
#include <string>
#include <memory>
#include <mutex>
#include <fstream>
#include <thread>
#include <sstream>
#include "Common/Configuration.h"

class Logger
{
public:

    static std::shared_ptr<Logger> log();
    void debugMessage(std::string const & message);
    void infoMessage(std::string const & message);
    void warningMessage(std::string const & message);
    void errorMessage(std::string const & message);
    void fatalError(std::string const & message);

    ~Logger()
    {
        logOut.close();
    }

    Logger(Logger const &) = delete;
    Logger(Logger &&) = delete;
    Logger& operator=(Logger const &) = delete;
    Logger& operator=(Logger &&) = delete;

protected:
    Logger();
    static std::shared_ptr<Logger> _logger;

private:
    std::mutex outputMutex;
    std::ofstream logOut;
    std::string createLogString(std::string const & level, std::string const & message);
};


