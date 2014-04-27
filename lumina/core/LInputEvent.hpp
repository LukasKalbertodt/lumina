#pragma once
/**
 * \file LInputEvent.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file defines some enums and structs used for input events (mouse
 * and keyboard).
 */
#include "LKeyCode.hpp"

#include <cstring>

namespace lumina {

// type of input event
enum class LInputType {
  KeyInput,
  MouseInput
};

// type of mouse event
enum class LMouseEventType {
  LButtonPressed, 
  MButtonPressed,
  RButtonPressed,
  LButtonReleased,
  MButtonReleased,
  RButtonReleased,
  MouseMoveDirection,
  MouseMovePosition
};

// data about mouse input event
struct LMouseInput {
  int x;
  int y;
  int wheel;
  LMouseEventType type;
};

// type of key event
enum LKeyEventType {
  KeyReleased,
  KeyPressed,
  KeyHold,
  Character
};

// data about key input event
struct LKeyInput {
  LKeyCode key;
  unsigned char c;
  LKeyEventType type;
};

// input event 
struct LInputEvent {
  LInputType type;

  union {
    LKeyInput keyInput;
    LMouseInput mouseInput;
  };

  LInputEvent() {
    memset(this, 0, sizeof(*this));
  }
};

// says what was done with the event
enum class LEventResult {
  Skipped,
  Processed
};

} // namespace lumina