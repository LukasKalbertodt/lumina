namespace lumina {

inline void SingleBase::setServiceContext(config::ServiceContext cnt) {}


#define XGenLog(funcName_, level_)                                             \
  template <typename... Ts> void SingleBase::funcName_(Ts... args) {           \
    getLoggerService(config::defaultServiceContext)                            \
      .log<LogLevel::level_>(args...);                                         \
  }


XGenLog(logCritical, Critical)
XGenLog(logError, Error)
XGenLog(logWarning, Warning)
XGenLog(logNotice, Notice)
XGenLog(log, Info)
XGenLog(logDebug, Debug)

#undef XGenLog

}