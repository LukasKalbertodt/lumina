#pragma once

#include "RenderContext.hpp"
#include "Window.fpp"
#include "../config/BaseProxy.hpp"
#include "../input/InputEvent.hpp"
#include "../input/WindowEvent.hpp"
#include "../util/VectorCore.hpp"

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct GLFWwindow;

namespace lumina {

enum class CursorMode : uint8_t {
  Normal, Hidden, Free
};

/** A Window from which a RenderContext can be obtained.
This is the first object you need in order to do anything else. The window is
responsible for polling events of all kinds, containing all window properties 
(as size and title), handling the OpenGL function and some more things. 

After creating an instance of Window you should call setVersionHint() to 
request a specific OpenGL version. If it isn't called, open() will fail in 
most cases.
*/
class Window : public config::CommonBase {
public:
  /** Creates a new Window but does not open it.
  \param title Title of the window (can be set via setTitle())
  \param size Size of the window (can be set via resize())
  */
  Window(std::string title = "Lumina Application",
         Vec2i size = Vec2i(600, 400));
  ~Window();

  /// Functor type for handling InputEvents
  using EventCallback = std::function<EventResult(InputEvent)>;

  /// Type for accessing a specific EventCallback
  using EventCallbackIndex = std::vector<EventCallback>::size_type;

  /// Functor type for handling WindowEvents
  using WindowCallback = std::function<EventResult(WindowEvent)>;

  ///Type for accessing a specific WindowCallback 
  using WindowCallbackIndex = std::vector<WindowCallback>::size_type;

  /** Sets a hint which OpenGL version to use to create the context.
  The underlying implementation might ignore the hint. If this is the case
  a warning is logged. 
  \note This function must be called before open()!
  \param major The major version digit
  \param minor The minor version digit
  */
  void setVersionHint(int major, int minor = 0);

  void setResizable(bool enable);

  void setSizeMultiplier(float multi);

  /** Disables or enables VSync
  If VSync is enabled RenderContext::swapBuffers will be synchronized with
  the screen refresh rate. 
  \param enable True to enable VSync
  */
  void setVSync(bool enable);
  
  /// Changes the title of the window
  void setTitle(std::string title);
  
  /// Resizes the window 
  void resize(Vec2i size);
  
  /// Sets the mode of the mouse cursor
  void setCursorMode(CursorMode mode);

  /// Returns the current size of the window
  Vec2i getSize();

  /// Returns the OpenGL context for this window.
  RenderContext& getRenderContext();

  /** Opens the window.
  \note Currently "open window" implies "creating render context" because we 
  use GLFW
  */
  void open();

  /// Closes window and free resources
  void close();

  /// Check for new events 
  void pollEvents();

  /** check for events and window status.
  This method should be called every frame to ensure the window behaves 
  properly.
  */
  void update();

  /** Returns if the window is valid.
  The window can become invalid when the X Button is pressed or for some other
  reasons. You should always check if the window is still valid. In case this
  method returns false you should close the window. If you don't close it and
  update() is called twice after that, the window will close itself.
  */
  bool isValid();

  /** Add a callback to process InputEvents.
  \return A callback index. It's neccessary for deleting the callback later on.
  */
  EventCallbackIndex addEventCallback(EventCallback&& callback);
  
  /** Removes an InputEvent callback with the index previously returned by
  addEventCallback.
  \note This method should not be called regularly.
  */
  void removeEventCallback(EventCallbackIndex index);

  /** Add a callback to process WindowEvents.
  \return A callback index. It's neccessary for deleting the callback later on.
  */
  WindowCallbackIndex addWindowCallback(WindowCallback&& callback);

  /** Removes an WindowEvent callback with the index previously returned by
  addWindowCallback.
  \note This method should not be called regularly.
  */
  void removeWindowCallback(WindowCallbackIndex index);

private:
  GLFWwindow* m_window;
  Vec2i m_size;
  std::pair<std::int16_t, std::int16_t> m_version;
  std::string m_title;  // TODO: check if we need this
  std::unique_ptr<RenderContext> m_renderContext;
  std::vector<InputEvent> m_eventQueue;
  std::vector<EventCallback> m_eventCallbacks;
  std::vector<WindowEvent> m_windowEventQueue;
  std::vector<WindowCallback> m_windowCallbacks;
  float m_lastMouseX, m_lastMouseY;
  float m_sizeMultiplier;
  bool m_resetLastPos;
  bool m_resizable;
  bool m_fullscreen;
  CursorMode m_cursorMode;


  void postEvent(InputEvent e);
  void postWindowEvent(WindowEvent e);

  static std::map<GLFWwindow*, Window*> s_eventReceiver;

  static void resizeCallback(GLFWwindow* win, int width, int height);
  static void keyCallback(GLFWwindow* win,
                          int key,
                          int scancode,
                          int action,
                          int mods);
  static void charCallback(GLFWwindow* win, unsigned int key);
  static void mouseButtonCallback(GLFWwindow* win,
                                  int button,
                                  int action,
                                  int mods);
  static void mousePosCallback(GLFWwindow* w, double xpos, double ypos);
  static void mouseScrollCallback(GLFWwindow* w, double x, double y);
  static void windowCloseCallback(GLFWwindow* w);
};

}

#include "Window.tpp"
