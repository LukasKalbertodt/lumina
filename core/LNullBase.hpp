#pragma once
/**
 * \file LSNullBase.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * LNullBase is an implementation of the lumina base. Nearly all classes in 
 * the lumina framework share one base: config::CommonBase. This base is used 
 * for provide cross cutting concerns (so called services), such as logging.
 * The user of the lumina framework can configure which base to use or define 
 * it's own base. This configuration is done in L/config/BaseProxy.hpp
 * Each base must fulfill the interface of a lumina base. LNullBase is an 
 * example for one implementation, which does nothing. Here you can read what
 * the methods should do. 
 * Most of the time you want to use either LContextBase or LSingleBase. For 
 * more information see the corresponding file.
 * If you don't want to have any of those services, you can use LNullBase, 
 * which does nothing and shouldn't have any overhead (with some compiler 
 * optimizations).
 */
#include "LConfig.hpp"

namespace lumina {

class LNullBase {
public:
  /**
   * @brief Sets the context of the service. Used only by LContextBase.
   * 
   * @param cnt Service context
   */
  void setServiceContext(config::ServiceContext cnt) {}

protected:

  /**
   * @brief Logs information. You can configure the LoggerService associated
   * with your service context to specify how information is logged.
   * 
   * @param args Arbitrary information
   */
  template <typename... Ts> void log(Ts... args) {}

  /**
   * @brief Logs information about an error. See log for more details.
   * 
   * @param args Arbitrary information
   */
  template <typename... Ts> void logError(Ts... args) {}

  /**
   * @brief Logs information about a warning. See log for more details.
   * 
   * @param args Arbitrary information
   */
  template <typename... Ts> void logWarning(Ts... args) {}
};


}