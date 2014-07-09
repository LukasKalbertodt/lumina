namespace lumina {

inline ContextBase::ContextBase() : m_context(config::defaultServiceContext) {}

inline void ContextBase::setServiceContext(config::ServiceContext cnt) {
  m_context = cnt;
}

#define XGenLog(funcName_, level_)                                             \
  template <typename... Ts> void ContextBase::funcName_(Ts... args) {          \
    getLoggerService(m_context).log<LogLevel::level_>(args...);                \
  }


XGenLog(logCritical, Critical)
XGenLog(logError, Error)
XGenLog(logWarning, Warning)
XGenLog(logNotice, Notice)
XGenLog(log, Info)
XGenLog(logDebug, Debug)

#undef XGenLog

}