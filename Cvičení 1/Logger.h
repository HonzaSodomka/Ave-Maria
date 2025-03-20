#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>

enum class Severity {
    DEBUG,
    INFO,
    WARNING,
    ERR,
    CRITICAL
};

class Logger
{
public:
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
    static void critical(const std::string& message);

private:
    static void log(Severity severity, const std::string& message);
};

