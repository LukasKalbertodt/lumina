#pragma once

#include "../input/KeyCode.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace lumina {

inline KeyCode translateGLFWKey(int key) {
  switch(key)  {
    case GLFW_KEY_BACKSPACE:     return KeyCode::Backspace;
    case GLFW_KEY_TAB:           return KeyCode::Tab;
    case GLFW_KEY_KP_ENTER:
    case GLFW_KEY_ENTER:         return KeyCode::Return;
    case GLFW_KEY_LEFT_SHIFT:
    case GLFW_KEY_RIGHT_SHIFT:   return KeyCode::Shift;
    case GLFW_KEY_LEFT_CONTROL:
    case GLFW_KEY_RIGHT_CONTROL: return KeyCode::Control;
    case GLFW_KEY_LEFT_ALT:
    case GLFW_KEY_RIGHT_ALT:     return KeyCode::Alt;
    case GLFW_KEY_PAUSE:         return KeyCode::Pause;
    case GLFW_KEY_CAPS_LOCK:     return KeyCode::Capital;
    case GLFW_KEY_ESCAPE:        return KeyCode::Escape;
    case GLFW_KEY_SPACE:         return KeyCode::Space;
    case GLFW_KEY_PAGE_UP:       return KeyCode::Pageup;
    case GLFW_KEY_PAGE_DOWN:     return KeyCode::Pagedown;
    case GLFW_KEY_END:           return KeyCode::End;
    case GLFW_KEY_HOME:          return KeyCode::Home;
    case GLFW_KEY_LEFT:          return KeyCode::Left;
    case GLFW_KEY_UP:            return KeyCode::Up;
    case GLFW_KEY_RIGHT:         return KeyCode::Right;
    case GLFW_KEY_DOWN:          return KeyCode::Down;
    case GLFW_KEY_PRINT_SCREEN:  return KeyCode::Snapshot;
    case GLFW_KEY_INSERT:        return KeyCode::Insert;
    case GLFW_KEY_DELETE:        return KeyCode::Delete;
    case GLFW_KEY_0:             return KeyCode::K0;
    case GLFW_KEY_1:             return KeyCode::K1;
    case GLFW_KEY_2:             return KeyCode::K2;
    case GLFW_KEY_3:             return KeyCode::K3;
    case GLFW_KEY_4:             return KeyCode::K4;
    case GLFW_KEY_5:             return KeyCode::K5;
    case GLFW_KEY_6:             return KeyCode::K6;
    case GLFW_KEY_7:             return KeyCode::K7;
    case GLFW_KEY_8:             return KeyCode::K8;
    case GLFW_KEY_9:             return KeyCode::K9;
    case GLFW_KEY_A:             return KeyCode::A;
    case GLFW_KEY_B:             return KeyCode::B;
    case GLFW_KEY_C:             return KeyCode::C;
    case GLFW_KEY_D:             return KeyCode::D;
    case GLFW_KEY_E:             return KeyCode::E;
    case GLFW_KEY_F:             return KeyCode::F;
    case GLFW_KEY_G:             return KeyCode::G;
    case GLFW_KEY_H:             return KeyCode::H;
    case GLFW_KEY_I:             return KeyCode::I;
    case GLFW_KEY_J:             return KeyCode::J;
    case GLFW_KEY_K:             return KeyCode::K;
    case GLFW_KEY_L:             return KeyCode::L;
    case GLFW_KEY_M:             return KeyCode::M;
    case GLFW_KEY_N:             return KeyCode::N;
    case GLFW_KEY_O:             return KeyCode::O;
    case GLFW_KEY_P:             return KeyCode::P;
    case GLFW_KEY_Q:             return KeyCode::Q;
    case GLFW_KEY_R:             return KeyCode::R;
    case GLFW_KEY_S:             return KeyCode::S;
    case GLFW_KEY_T:             return KeyCode::T;
    case GLFW_KEY_U:             return KeyCode::U;
    case GLFW_KEY_V:             return KeyCode::V;
    case GLFW_KEY_W:             return KeyCode::W;
    case GLFW_KEY_X:             return KeyCode::X;
    case GLFW_KEY_Y:             return KeyCode::Y;
    case GLFW_KEY_Z:             return KeyCode::Z;
    case GLFW_KEY_LEFT_SUPER:    return KeyCode::LWin;
    case GLFW_KEY_RIGHT_SUPER:   return KeyCode::RWin;
    case GLFW_KEY_MENU:          return KeyCode::Apps;
    case GLFW_KEY_KP_0:          return KeyCode::Numpad0;
    case GLFW_KEY_KP_1:          return KeyCode::Numpad1;
    case GLFW_KEY_KP_2:          return KeyCode::Numpad2;
    case GLFW_KEY_KP_3:          return KeyCode::Numpad3;
    case GLFW_KEY_KP_4:          return KeyCode::Numpad4;
    case GLFW_KEY_KP_5:          return KeyCode::Numpad5;
    case GLFW_KEY_KP_6:          return KeyCode::Numpad6;
    case GLFW_KEY_KP_7:          return KeyCode::Numpad7;
    case GLFW_KEY_KP_8:          return KeyCode::Numpad8;
    case GLFW_KEY_KP_9:          return KeyCode::Numpad9;
    case GLFW_KEY_KP_MULTIPLY:   return KeyCode::Multiply;
    case GLFW_KEY_KP_ADD:        return KeyCode::Add;
    case GLFW_KEY_KP_SUBTRACT:   return KeyCode::Subtract;
    case GLFW_KEY_KP_DECIMAL:    return KeyCode::Decimal;
    case GLFW_KEY_KP_DIVIDE:     return KeyCode::Divide;
    case GLFW_KEY_F1:            return KeyCode::F1;
    case GLFW_KEY_F2:            return KeyCode::F2;
    case GLFW_KEY_F3:            return KeyCode::F3;
    case GLFW_KEY_F4:            return KeyCode::F4;
    case GLFW_KEY_F5:            return KeyCode::F5;
    case GLFW_KEY_F6:            return KeyCode::F6;
    case GLFW_KEY_F7:            return KeyCode::F7;
    case GLFW_KEY_F8:            return KeyCode::F8;
    case GLFW_KEY_F9:            return KeyCode::F9;
    case GLFW_KEY_F10:           return KeyCode::F10;
    case GLFW_KEY_F11:           return KeyCode::F11;
    case GLFW_KEY_F12:           return KeyCode::F12;
    case GLFW_KEY_F13:           return KeyCode::F13;
    case GLFW_KEY_F14:           return KeyCode::F14;
    case GLFW_KEY_F15:           return KeyCode::F15;
    case GLFW_KEY_F16:           return KeyCode::F16;
    case GLFW_KEY_F17:           return KeyCode::F17;
    case GLFW_KEY_F18:           return KeyCode::F18;
    case GLFW_KEY_F19:           return KeyCode::F19;
    case GLFW_KEY_F20:           return KeyCode::F20;
    case GLFW_KEY_F21:           return KeyCode::F21;
    case GLFW_KEY_F22:           return KeyCode::F22;
    case GLFW_KEY_F23:           return KeyCode::F23;
    case GLFW_KEY_F24:           return KeyCode::F24;
    case GLFW_KEY_NUM_LOCK:      return KeyCode::Numlock;
    case GLFW_KEY_SCROLL_LOCK:   return KeyCode::Scroll;
    case GLFW_KEY_SEMICOLON:     return KeyCode::OEM_1;
    case GLFW_KEY_SLASH:         return KeyCode::OEM_2;
    case GLFW_KEY_GRAVE_ACCENT:  return KeyCode::OEM_3;
    case GLFW_KEY_LEFT_BRACKET:  return KeyCode::OEM_4;
    case GLFW_KEY_BACKSLASH:     return KeyCode::OEM_5;
    case GLFW_KEY_RIGHT_BRACKET: return KeyCode::OEM_6;
    case GLFW_KEY_APOSTROPHE:    return KeyCode::OEM_7;
    case GLFW_KEY_WORLD_1:       return KeyCode::OEM_8;
    case GLFW_KEY_WORLD_2:       return KeyCode::OEM_102;
    case GLFW_KEY_EQUAL:         return KeyCode::OEM_Plus;
    case GLFW_KEY_COMMA:         return KeyCode::OEM_Comma;
    case GLFW_KEY_MINUS:         return KeyCode::OEM_Minus;
    case GLFW_KEY_PERIOD:        return KeyCode::OEM_Period;
    default: return KeyCode::None;
  }
}

} // namespace lumina