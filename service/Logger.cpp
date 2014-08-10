#include "Logger.hpp"
#include "ServiceProvider.hpp"

namespace lumina {

std::vector<Logger*> Logger::s_instances;

std::string Logger::getTimeString() {
  using namespace std::chrono;
  auto now = Clock::now();
  auto diff = now - m_time;

  int msec = duration_cast<milliseconds>(diff).count() % 10000;
  int sec  = duration_cast<seconds>(diff).count() % 60;
  int min  = duration_cast<minutes>(diff).count() % 100;

  char out[] = "00:00.0000";
  std::snprintf(out, 11, "%.2i:%.2i.%.4i", min, sec, msec);

  return std::string(out);
}

void Logger::setGlobalStdLevelFilter(LogLevel required) {
  // generate all loggers
  getLoggerService(config::defaultServiceContext);
  for(Logger* logger : s_instances) {
    logger->setStdLevelFilter(required);
  }
}

void Logger::setGlobalStdLogging(bool enable) {
  // generate all loggers
  getLoggerService(config::defaultServiceContext);
  for(Logger* logger : s_instances) {
    logger->setStdLogging(enable);
  }
}

void Logger::setGlobalLogFileName(std::string filename) {
  // generate all loggers
  getLoggerService(config::defaultServiceContext);
  for(Logger* logger : s_instances) {
    logger->setLogFileName(filename);
  }
}



}