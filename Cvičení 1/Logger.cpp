#include "Logger.h"

void Logger::debug(const std::string& message)
{
	Logger::log(Severity::DEBUG, message);
}

void Logger::info(const std::string& message)
{
	Logger::log(Severity::INFO, message);
}

void Logger::warning(const std::string& message)
{
	Logger::log(Severity::WARNING, message);
}

void Logger::error(const std::string& message)
{
	Logger::log(Severity::ERR, message);
}

void Logger::critical(const std::string& message)
{
	Logger::log(Severity::CRITICAL, message);
}

void Logger::log(Severity severity, const std::string& message)
{
    {
        std::time_t now = std::time(nullptr);
        std::tm tm_now;
        localtime_s(&tm_now, &now);

        std::cout << "[" << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << "] ";

        switch (severity) {
        case Severity::DEBUG:
            std::cout << "[DEBUG]";
            break;
        case Severity::INFO:
            std::cout << "[INFO]";
            break;
        case Severity::WARNING:
            std::cout << "[WARNING]";
            break;
        case Severity::ERR:
            std::cout << "[ERROR]";
            break;
        case Severity::CRITICAL:
            std::cout << "[CRITICAL]";
            break;
        }

        std::cout << "\t";
        std::cout << message;
        std::cout << std::endl;
    }
}
