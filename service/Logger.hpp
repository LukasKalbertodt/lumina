#pragma once

#include "../config/LConfig.hpp"
#include "../core/LogLevel.hpp"
#include "../util/TerminalLook.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

namespace lumina {

class Logger {
public:
  Logger();
    

  /*****************************************************************************
   * Logging functions
   ****************************************************************************/
  /**
   * @brief Log information
   * @param msgs values to log
   */
  template <LogLevel LL = LogLevel::Info, typename... Ts>
  void log(Ts... msgs);

  /**
   * @brief Log information
   * @param msgs values to log
   */
  template <typename... Ts> void logWarning(Ts... msgs);

  /**
   * @brief Log information
   * @param msgs values to log
   */
  template <typename... Ts> void logError(Ts... msgs);

  /**
   * @brief Set the name of the file, which is used for logging
   * @param filename Name of the file
   */
  void setLogFileName(std::string filename) {
    m_logFileName = filename;
    if(!filename.empty())
      openLogFile();
  }

  /**
   * @brief Enable or disable logging via cout and cerr
   * @param enable true if enabled
   */
  void setStdLogging(bool enable) {
    m_stdIO = enable;
  }


private:
  using Clock = std::chrono::system_clock;

  std::string m_logFileName;
  bool m_stdIO;
  Clock::time_point m_time;
  std::ofstream m_logFile;





  void openLogFile() {
    // try to open log file
    m_logFile.open(m_logFileName, std::ios::app | std::ios::ate);
    if(!m_logFile) {
      std::cerr << "Failed to open log file (" 
                << m_logFileName << ")!" << std::endl;
    }

    // write header
    m_logFile << std::endl << "---------------------------------------" 
              << std::endl;
    m_logFile << "Opened log file: " << m_logFileName 
              << std::endl;
  }

  template <typename T, typename... Ts>
  void logStdIO(T head, Ts... tail) {
    logStdIO(head);
    logStdIO(tail...);
  }
  template <typename T>
  void logStdIO(T msg) {
    std::cout << msg;
  }

  template <typename T, typename... Ts>
  void logFile(T head, Ts... tail) {
    logFile(head);
    logFile(tail...);
  }
  template <typename T>
  void logFile(T msg) {
    m_logFile << msg;
  }

  std::string getTimeString();
};


} // namespace lumina

#include "Logger.tpp"