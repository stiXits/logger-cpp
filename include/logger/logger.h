#ifndef LOGGER_H
#define LOGGER_H

#include <functional>

#define LOG(logger, loglevel, expression)                                      \
  if (logger->getLogLevel() <= loglevel) {                                     \
    logger->log(loglevel, expression);                                         \
  }

namespace Logging {
enum class LogLevel {
  trace = 0,
  debug = 1,
  info = 2,
  warn = 3,
  error = 4,
  fatal = 5
};

class Logger {
public:
  using LoggerCallbackType = std::function<void(const std::string &)>;

  Logger();
  virtual ~Logger();

  virtual LogLevel setLogLevel(const LogLevel logLevel);
  virtual LogLevel getLogLevel() const;
  virtual void log(const LogLevel loglevel,
                   const std::string &logMessage) const;
  virtual void setLoggerCallback(const LogLevel loglevel,
                                 const LoggerCallbackType &callback);

private:
  LoggerCallbackType trace;
  LoggerCallbackType debug;
  LoggerCallbackType info;
  LoggerCallbackType warn;
  LoggerCallbackType error;
  LoggerCallbackType fatal;

  LogLevel currentLogLevel;
};
} // namespace Logging

#endif // LOGGER_H
