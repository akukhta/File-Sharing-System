#include "Logger.h"

std::shared_ptr<Logger> Logger::_logger = nullptr;

Logger::Logger()
{   
    logOut.open("serverLog.txt", std::ios_base::app);
}

std::shared_ptr<Logger> Logger::log()
{
    if (!_logger)
        _logger = std::shared_ptr<Logger>(new Logger);

    return _logger;
}

void Logger::debugMessage(const std::string &message)
{
    std::lock_guard lock(outputMutex);
    auto x = createLogString("debug", message);
    logOut << x;
}

void Logger::infoMessage(const std::string &message)
{
    std::lock_guard lock(outputMutex);
    logOut << createLogString("info", message);
}

void Logger::warningMessage(const std::string &message)
{
    std::lock_guard lock(outputMutex);
    logOut << createLogString("warning", message);
}

void Logger::errorMessage(const std::string &message)
{
    std::lock_guard lock(outputMutex);
    logOut << createLogString("error", message);
}

void Logger::fatalError(const std::string &message)
{
    std::lock_guard lock(outputMutex);
    logOut << createLogString("fatal", message);
}

std::string Logger::createLogString(std::string const & level, std::string const & message)
{
    std::stringstream ss;
    ss << "[" << Configuration::getCurrentTimeAsStdString() << "] ["
            << std::this_thread::get_id() << "] [" << level << "] " << message;
    return ss.str();
}
