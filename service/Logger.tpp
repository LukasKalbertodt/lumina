namespace lumina {

inline Logger::Logger()
  : m_stdIO(config::useLogStandardIO),
    m_time(Clock::now()),
    m_requiredStdLevel(LogLevel::Debug) {
  s_instances.push_back(this);
}

template <LogLevel LL, typename... Ts> 
void Logger::log(Ts... msgs) {
  if(m_stdIO && LL >= m_requiredStdLevel) {
    switch(LL) {
      case LogLevel::Critical:
        logStdIO(TL::RedBG, TL::White, "[", getTimeString(), " CRIT]", 
                 TL::ResetBG, TL::Red, msgs..., TL::ResetText);
        break;
      case LogLevel::Error:
        logStdIO(TL::Red, "[", getTimeString(), " ERROR]",
                 msgs..., TL::ResetText);
        break;
      case LogLevel::Warning: 
        logStdIO(TL::Yellow, "[", getTimeString(), " WARN]",
                 msgs..., TL::ResetText);
        break;
      case LogLevel::Notice: 
        logStdIO(TL::White, "[", getTimeString(), " NOTE]",
                 msgs..., TL::ResetText);
        break;
      case LogLevel::Info: 
        logStdIO("[", getTimeString(), " INFO]", msgs...);
        break;
      case LogLevel::Debug:
        if(!config::ignoreDebugLogs) {
          logStdIO(TL::Thin, "[", getTimeString(), " DEBUG]", msgs..., 
                   TL::ResetWeight);
        }
        break;
    }

    std::cout << std::endl;
  }

  if(m_logFile && m_logFile.is_open()) {
    logFile("[", getTimeString(), "]", msgs...);
    m_logFile << std::endl;
  }
}

inline void Logger::setLogFileName(std::string filename) {
  m_logFileName = filename;
  if(!filename.empty()) {
    openLogFile();
  }
}
inline void Logger::setGlobalLogFileName(std::string filename) {
  // generate all loggers
  getLoggerService(config::defaultServiceContext);
  for(Logger* logger : s_instances) {
    logger->setLogFileName(filename);
  }
}


inline void Logger::setStdLogging(bool enable) { 
  m_stdIO = enable; 
}

inline void Logger::setGlobalStdLogging(bool enable) {
  // generate all loggers
  getLoggerService(config::defaultServiceContext);
  for(Logger* logger : s_instances) {
    logger->setStdLogging(enable);
  }
}


inline void Logger::setStdLevelFilter(LogLevel required) {
  m_requiredStdLevel = required;
}

inline void Logger::setGlobalStdLevelFilter(LogLevel required) {
  // generate all loggers
  getLoggerService(config::defaultServiceContext);
  for(Logger* logger : s_instances) {
    logger->setStdLevelFilter(required);
  }
}


}