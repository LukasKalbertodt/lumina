#pragma once 

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