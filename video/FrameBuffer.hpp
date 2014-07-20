#pragma once

#include "GLObject.hpp"
#include "Texture.hpp"
#include "HotFrameBuffer.fpp"
#include "FBAttPoints.hpp"

#include <GL/glew.h>
#include <functional>
#include <memory>
#include <vector>

namespace lumina {
namespace internal {

class FrameBufferInterface : public GLObject {
public:
  virtual ~FrameBufferInterface() = default;

  virtual void create() = 0;
  virtual void prime(std::shared_ptr<FrameBufferInterface> fb,
                     std::function<void(HotFrameBuffer&)> func) = 0;
  virtual void attachColor(int index, const Tex2D& tex) = 0;

protected:
  // true if a user defined framebuffer is primed
  static bool s_userPrimed;
};

class UserFrameBuffer : public FrameBufferInterface {
public:
  UserFrameBuffer();
  UserFrameBuffer(UserFrameBuffer&&);

  ~UserFrameBuffer();

  void create() override final;
  void prime(std::shared_ptr<FrameBufferInterface> fb,
             std::function<void(HotFrameBuffer&)> func) override final;
  void attachColor(int index, const Tex2D& tex) override final;


  // internal::ColorAttSet colors;


private:
  GLuint m_handle;
  std::vector<internal::ColorAttPoint> m_colorAtts;
  bool m_needsUpdate;

  void updateState();
  void bind();
  void unbind();
};

} // namespace internal


/**
 * @brief Wrapper for either a UserFrameBuffer or the DefaultFrameBuffer 
 *        (provides a layer of indirection)
 * @details If created, it creates a UserFrameBuffer internally
 */
class FrameBuffer : public NotCopyable {
public:
  FrameBuffer();
  FrameBuffer(std::shared_ptr<internal::FrameBufferInterface> fb);

  void create();
  void prime(std::function<void(HotFrameBuffer&)> func);
  void attachColor(int index, const Tex2D& tex);

private:
  std::shared_ptr<internal::FrameBufferInterface> m_fb;
};

}

#include "FrameBuffer.tpp"