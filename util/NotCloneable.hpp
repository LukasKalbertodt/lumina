#pragma once

namespace lumina {

class NotCopyable {
protected:
  NotCopyable() = default;
  NotCopyable(const NotCopyable&) = delete;
  NotCopyable& operator=(const NotCopyable&) = delete;
};

class NotMoveable {
protected:
  NotMoveable() = default;
  NotMoveable(NotMoveable&&) = delete;
  NotMoveable& operator==(NotMoveable&&) = delete;
};

class NotCloneable : public NotCopyable, public NotMoveable {};

}