namespace lumina {

inline Logger::Logger()
  : m_stdIO(config::useLogStandardIO), m_time(Clock::now()) {}

template <LogLevel LL, typename... Ts> 
void Logger::log(Ts... msgs) {
  if(m_stdIO) {
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
        logStdIO("[", getTimeString(), " DEBUG]", msgs...);
        break;
    }

    std::cout << std::endl;
  }

  if(m_logFile && m_logFile.is_open()) {
    logFile("[", getTimeString(), "]", msgs...);
    m_logFile << std::endl;
  }
}

template <typename... Ts> 
void Logger::logWarning(Ts... msgs) {
  log<LogLevel::Warning>(msgs...);
}

template <typename... Ts> 
void Logger::logError(Ts... msgs) {
  log<LogLevel::Error>(msgs...);
}


inline std::string Logger::getTimeString() {
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

}