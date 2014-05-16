#pragma once

#include "LGLTools.hpp"
#include "PrimitiveType.hpp"
#include "LVertexLayout.hpp"
#include "../config/BaseProxy.hpp"
#include "../core/LGLException.hpp"  
#include "../util/VariadicTools.hpp"

#include <GL/glew.h>
#include <cstddef>
#include <memory>


namespace lumina {

template <typename...>
class HotMesh;

class LMesh : public config::CommonBase {
public:
  // default constructor
  LMesh()
    : m_vertexHandle(0),
      m_indexHandle(0),
      m_vertexArrayObject(0),
      m_vertexCount(0),
      m_indexCount(0),
      m_primitiveType(GL_TRIANGLES) {}

  LMesh(int vertexCount) : LMesh() {
    create(vertexCount);
  }
  LMesh(int vertexCount, int indexCount) : LMesh() {
    create(vertexCount, indexCount);
  }

  // copy constructor and copy assignment operator
  LMesh(const LMesh& copy);
  LMesh& operator=(const LMesh& copy);


  // move constructor and move assignment operator
  LMesh(LMesh&& m);
  LMesh& operator=(LMesh&& m);

  // destructor
  ~LMesh();

  void create(int vertexCount);
  void create(int vertexCount, int indexCount);
  template <typename... Cs, typename L>
  void apply(L lambda);
  void sendData() {
    bindVAO();
    bindVBO();
    glDrawArrays(m_primitiveType, 0, 3);
  }


protected:
  GLuint m_vertexHandle;
  GLuint m_indexHandle;
  GLuint m_vertexArrayObject;
  std::size_t m_vertexCount;
  std::size_t m_indexCount;
  GLenum m_primitiveType;

  std::size_t vertexCount() const { return m_vertexCount; }
  std::size_t indexCount() const { return m_indexCount; }
  std::size_t vertexSize() const { return m_vertexCount * 4; }
  std::size_t indexSize() const { return m_indexCount * 4; }

  void setPrimitiveType(PrimitiveType type) {
    switch(type) {
      case PrimitiveType::Point:
        m_primitiveType = GL_POINTS;
        break;
      case PrimitiveType::Triangle:
        m_primitiveType = GL_TRIANGLES;
        break;
      case PrimitiveType::TriangleStrip:
        m_primitiveType = GL_TRIANGLE_STRIP;
        break;
    }
  }

  void bindVAO();
  void bindVBO();

  template <typename... Cs>
  friend class HotMesh;
};

template <typename... Cs>
class HotMesh : public LMesh {
private:
  HotMesh(LMesh& ref) : vertex(ref.m_vertexCount) {
    this->m_vertexHandle = ref.m_vertexHandle;
    this->m_indexHandle = ref.m_indexHandle;
    this->m_vertexArrayObject = ref.m_vertexArrayObject;
    this->m_vertexCount = ref.m_vertexCount;
    this->m_indexCount = ref.m_indexCount;

    bindVAO();
    bindVBO();

    auto err = glGetError();
    if(err != GL_NO_ERROR) {
      logError("[LMesh] Error <",
               translateGLError(err),
               "> while creating hot mesh!");
      throw LGLException("Error while creating hot mesh");
    }

    GLbitfield mode = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;
    vertex.m_buf = glMapBufferRange(GL_ARRAY_BUFFER, 0, vertexSize(), mode);
  }
  friend LMesh;

  class BufferWriter {
  private:
    template <typename T, typename... Ts>
    class CommaBufferWriter {
    private:
      void* m_buf;

    public:
      CommaBufferWriter(void* ptr) : m_buf(ptr) {}
      CommaBufferWriter<Ts...> operator,(T data) {
        *static_cast<T*>(m_buf) = data;
        return CommaBufferWriter<Ts...>(static_cast<T*>(m_buf) + 1);
      }
    };

    template <typename T>
    class CommaBufferWriter<T> {
      private:
      void* m_buf;

    public:
      CommaBufferWriter(void* ptr) : m_buf(ptr) {}
      void operator,(T data) {
        *static_cast<T*>(m_buf) = data;
      }
    };

    template <typename T, typename... Ts>
    class AssignBufferWriter {
    private:
      void* m_buf;

    public:
      AssignBufferWriter(void* ptr) : m_buf(ptr) {}

      CommaBufferWriter<Ts...> operator=(T data) {
        *static_cast<T*>(m_buf) = data;
        return CommaBufferWriter<Ts...>(static_cast<T*>(m_buf) + 1);
      }
    };
    template <typename T>
    class AssignBufferWriter<T> {
    private:
      void* m_buf;

    public:
      AssignBufferWriter(void* ptr) : m_buf(ptr) {}

      void operator=(T data) {
        *static_cast<T*>(m_buf) = data;
      }
    };

    void* m_buf;
    int m_vertexCount;
    friend HotMesh;

  public:
    BufferWriter(int vertexCount)
      : m_buf(nullptr), m_vertexCount(vertexCount) {}

    AssignBufferWriter<Cs...> operator[](int index) {
      if(index >= ((m_vertexCount*4)/internal::LayoutTypes<Cs...>::stride)) {
        throw LGLException("VertexWriter: Index out of bounds!");
      }
      return AssignBufferWriter<Cs...>(
        static_cast<char*>(m_buf)
        + index * internal::LayoutTypes<Cs...>::stride);
    }    
  };

public:
  // delete copy and move constructors to avoid copys
  HotMesh(const HotMesh&) = delete;
  HotMesh& operator=(const HotMesh&) = delete;
  HotMesh(HotMesh&&) = delete;
  HotMesh& operator==(HotMesh&&) = delete;

  // custom destructor
  // set handles to 0 so ~LMesh won't delete them (dirty hack...)
  ~HotMesh() {
    this->m_vertexHandle = 0;
    this->m_indexHandle = 0;
    this->m_vertexArrayObject = 0;

    // unmap vertex buffer
    glUnmapBuffer(GL_ARRAY_BUFFER);
  }

  // use functions of base class
  using LMesh::setPrimitiveType;
  void applyVertexLayout();

  BufferWriter vertex;

};


template <typename... Cs, typename L>
void LMesh::apply(L lambda) {
  HotMesh<Cs...> hot(*this);
  lambda(hot);
}

template <typename... Cs>
void HotMesh<Cs...>::applyVertexLayout() {
  internal::applyLayoutImpl<0,
                            internal::LayoutTypes<Cs...>::stride,
                            0,
                            sizeof(Cs)...>();
}

} // namespace lumina
