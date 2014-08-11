#pragma once
/**
 * \file InputEvent.hpp
 * This file defines some enums and structs used for input events (mouse
 * and keyboard).
 * 
 * This file is part of the Lumina Graphics Framework.
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 */
#include "KeyCode.hpp"

#include <cstdint>
#include <cstring>

namespace lumina {

/// Type of input event
enum class InputType : uint8_t {
  KeyRelease,     ///< A key was released
  KeyPressed,     ///< A key was pressed
  KeyHold,        ///< A key was hold (repeated by operating system)
  Char,           ///< A charachter input

  LMousePressed,  ///< Left mouse button was pressed
  MMousePressed,  ///< Middle mouse button was pressed
  RMousePressed,  ///< Right mouse button was pressed
  LMouseReleased, ///< Left mouse button was release
  MMouseReleased, ///< Middle mouse button was release
  RMouseReleased, ///< Right mouse button was release
  MouseMoveDir,   ///< Mouse was moved (delta) [mouse.x and mouse.y]
  MouseMovePos,   ///< Mouse was moved (absolute) [mouse.x and mouse.y]
  MouseScroll     ///< Mouse scrolled [mouse.scrollX and mouse.scrollY]
};

/// Additional data about a mouse input
struct MouseInput {
  union {
    struct { 
      float x;  ///< Absolute position or delta of mouse movement (x axis)
      float y;  ///< Absolute position or delta of mouse movement (y axis)
    }; 
    struct {
      float scrollX;  ///< Scroll delta (x)
      float scrollY;  ///< Scroll delta (y)
    };
  };
};

/// Additional data about a key input
struct KeyInput {
  KeyCode key;      ///< Contains the KeyCode of the pressed/released key
  unsigned char c;  ///< Contains the charachter of a charachter input
};

// input event 
struct InputEvent {
  InputType type;   ///< Type of the event

  union {
    KeyInput keyInput;      ///< Data for key input
    MouseInput mouseInput;  ///< Data for mouse input
  };

  InputEvent() {
    memset(this, 0, sizeof(*this));
  }
};

/// Result of a EventCallback: Was the event processed or skipped?
enum class EventResult {
  Skipped,    ///< The event was skipped: Other callbacks will be called
  Processed   ///< The event was processed: No other callback will be called
};

} // namespace lumina