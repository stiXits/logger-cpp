#include "logger/logger.h"

#include <iostream>
#include <string>

using namespace Logging;

decltype(auto) emptyCallback = [](auto) {};

Logger::Logger()
    : trace(emptyCallback), debug(emptyCallback), info(emptyCallback),
      warn(emptyCallback), error(emptyCallback), fatal(emptyCallback),
      currentLogLevel(LogLevel::trace) {}

Logger::~Logger() {}

LogLevel Logger::setLogLevel(const LogLevel logLevel) {
  return currentLogLevel = logLevel;
}

LogLevel Logger::getLogLevel() const { return currentLogLevel; }

void Logger::log(const LogLevel loglevel, const std::string &logMessage) const {
  if (loglevel == LogLevel::trace && currentLogLevel <= loglevel) {
    trace(logMessage);
  } else if (loglevel == LogLevel::debug && currentLogLevel <= loglevel) {
    debug(logMessage);
  } else if (loglevel == LogLevel::info && currentLogLevel <= loglevel) {
    info(logMessage);
  } else if (loglevel == LogLevel::warn && currentLogLevel <= loglevel) {
    warn(logMessage);
  } else if (loglevel == LogLevel::error && currentLogLevel <= loglevel) {
    error(logMessage);
  } else if (loglevel == LogLevel::fatal && currentLogLevel <= loglevel) {
    fatal(logMessage);
  }
}

void Logger::setLoggerCallback(const LogLevel loglevel,
                               const LoggerCallbackType &callback) {
  if (!callback) {
    throw std::runtime_error("callback must be a valid function");
  }

  switch (loglevel) {
  case LogLevel::trace:
    trace = callback;
    break;
  case LogLevel::debug:
    debug = callback;
    break;
  case LogLevel::info:
    info = callback;
    break;
  case LogLevel::warn:
    warn = callback;
    break;
  case LogLevel::error:
    error = callback;
    break;
  case LogLevel::fatal:
    fatal = callback;
    break;
  default:
    throw std::runtime_error("unknown loglevel");
  }
}
