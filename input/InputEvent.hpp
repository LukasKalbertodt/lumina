#pragma once
/**
 * \file InputEvent.hpp
 * This file is part of the Lumina Graphics Framework.
 * 
 * \author Lukas Kalbertodt <lukas.kalbertodt@gmail.com>
 * 
 * This file defines some enums and structs used for input events (mouse
 * and keyboard).
 */
#include "KeyCode.hpp"

#include <cstring>

namespace lumina {

// type of input event
enum class InputType {
  KeyInput,
  MouseInput
};

// type of mouse event
enum class MouseEventType {
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
struct MouseInput {
  int x;
  int y;
  int wheel;
  MouseEventType type;
};

// type of key event
enum KeyEventType {
  KeyReleased,
  KeyPressed,
  KeyHold,
  Character
};

// data about key input event
struct KeyInput {
  KeyCode key;
  unsigned char c;
  KeyEventType type;
};

// input event 
struct InputEvent {
  InputType type;

  union {
    KeyInput keyInput;
    MouseInput mouseInput;
  };

  InputEvent() {
    memset(this, 0, sizeof(*this));
  }
};

// says what was done with the event
enum class EventResult {
  Skipped,
  Processed
};

} // namespace lumina