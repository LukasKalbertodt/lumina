#pragma once 
/**
 * \file WindowEvent.hpp
 * Defines enums and structs that define a window event.
 * 
 * This file is part of the Lumina Graphics Framework.
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 */
namespace lumina {

enum class WindowEventType {
  None,
  Close
};

struct WindowEvent {
  WindowEventType type;

  WindowEvent() : type(WindowEventType::None) {}
};

}