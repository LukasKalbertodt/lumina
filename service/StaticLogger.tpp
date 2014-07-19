namespace lumina {


#define XGenLog(funcName_, level_)                                             \
  template <typename... Ts> void funcName_(Ts... args) {                       \
    getLoggerService(config::staticServiceContext)                             \
      .log<LogLevel::level_>(args...);                                         \
  }


XGenLog(slogCritical, Critical)
XGenLog(slogError, Error)
XGenLog(slogWarning, Warning)
XGenLog(slogNotice, Notice)
XGenLog(slog, Info)
XGenLog(slogDebug, Debug)

#undef XGenLog

template <typename Ex, LogLevel LL, typename... Ts> 
void slogAndThrow(Ts... args) {
  getLoggerService(config::staticServiceContext).log<LL>(args...);
  throw Ex(args...);
}



}