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
#include <iostream>


namespace lumina {

template <typename...>
class HotMesh;






class Mesh : public config::CommonBase {
public:
  // default constructor
  Mesh();

  Mesh(int vertexCount);
  Mesh(int vertexCount, int indexCount);

  // copy constructor and copy assignment operator
  Mesh(const Mesh& copy);
  Mesh &operator=(const Mesh &copy);

  // move constructor and move assignment operator
  Mesh(Mesh&& m);
  Mesh& operator=(Mesh&& m);

  // destructor
  ~Mesh();

  void create(int vertexCount);
  void create(int vertexCount, int indexCount);
  template <typename... Cs, typename L>
  void apply(L lambda);
  void sendData();


protected:
  GLuint m_vertexHandle;
  GLuint m_indexHandle;
  GLuint m_vertexArrayObject;
  std::size_t m_vertexCount;
  std::size_t m_indexCount;
  GLenum m_primitiveType;

  std::size_t vertexCount() const;
  std::size_t indexCount() const;
  std::size_t vertexSize() const;
  std::size_t indexSize() const;

  void setPrimitiveType(PrimitiveType type);

  void bindVAO();
  void bindVBO();

  template <typename... Cs>
  friend class HotMesh;
};















template <typename... Cs>
class HotMesh : public Mesh {
private:
  HotMesh(Mesh& ref);

  friend Mesh;

  class BufferWriter;

public:
  // delete copy and move constructors to avoid copys
  HotMesh(const HotMesh&) = delete;
  HotMesh& operator=(const HotMesh&) = delete;
  HotMesh(HotMesh&&) = delete;
  HotMesh& operator==(HotMesh&&) = delete;

  // custom destructor
  // set handles to 0 so ~Mesh won't delete them (dirty hack...)
  ~HotMesh() {
    this->m_vertexHandle = 0;
    this->m_indexHandle = 0;
    this->m_vertexArrayObject = 0;

    // unmap vertex buffer
    glUnmapBuffer(GL_ARRAY_BUFFER);
  }

  // use functions of base class
  using Mesh::setPrimitiveType;
  void applyVertexLayout();

  BufferWriter vertex;

};


template <typename... Cs, typename L>
void Mesh::apply(L lambda) {
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

template <typename... Cs>
class HotMesh<Cs...>::BufferWriter {
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
        std::cout << "blub" << m_buf << std::endl;
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


} // namespace lumina

#include "Mesh.tcc"