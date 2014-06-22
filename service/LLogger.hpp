#pragma once

#include "../config/LConfig.hpp"
#include "../util/TerminalColor.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

namespace lumina {

// TODO: tmp, this will be any class providing an ingame console
class LTerminal;

class LLogger {
public:
  LLogger() 
    : m_terminal(nullptr),
      m_stdIO(config::useLogStandardIO),
      m_time(Clock::now()) {
  }

  /*****************************************************************************
   * Logging functions
   ****************************************************************************/
  /**
   * @brief Log information
   * @param msgs values to log
   */
  template <typename... Ts>
  void log(Ts... msgs) {
    if(m_stdIO) {
      logStdIO("[", getTimeString(), "]", msgs...);
      std::cout << std::endl;
    }

    if(m_logFile && m_logFile.is_open()) {
      logFile("[", getTimeString(), "]", msgs...);
      m_logFile << std::endl;
    }

    if(m_terminal) {
    }
  }

  /**
   * @brief Log information
   * @param msgs values to log
   */
  template <typename... Ts>
  void logWarning(Ts... msgs) {
    if(m_stdIO) {
      logStdIO(LTFG::Yellow, "[", getTimeString(), " WARNING]", msgs..., LTC::Reset);
      std::cout << std::endl;
    }

    if(m_logFile && m_logFile.is_open()) {
      logFile("[", getTimeString(), " WARNING]", msgs...);
      m_logFile << std::endl;
    }

    if(m_terminal) {
    }
  }

  /**
   * @brief Log information
   * @param msgs values to log
   */
  template <typename... Ts>
  void logError(Ts... msgs) {
    if(m_stdIO) {
      logStdIO(LTFG::Red, "[", getTimeString(), " ERROR]", msgs..., LTC::Reset);
      std::cout << std::endl;
    }

    if(m_logFile && m_logFile.is_open()) {
      logFile("[", getTimeString(), " ERROR]", msgs...);
      m_logFile << std::endl;
    }

    if(m_terminal) {
    }
  }

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

  LTerminal* m_terminal;
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

  std::string getTimeString() {
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
};


} // namespace lumina