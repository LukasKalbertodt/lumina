#pragma once

#include "IndexSet.hpp"
#include "GLException.hpp"  
#include "GLTools.hpp"
#include "Mesh.fpp"
#include "PrimitiveType.hpp"
#include "VertexLayout.hpp"
#include "../config/BaseProxy.hpp"
#include "../util/VariadicTools.hpp"

#include <GL/glew.h>
#include <cstddef>
#include <memory>
#include <iostream>


namespace lumina {
// =============================================================================
// Definition of Mesh and HotMesh
// =============================================================================
/**
* \brief Represents a geometry mesh
* Mesh represents a collection of vertices with arbitrary attributes, which may
* be indexed. It uses an OpenGL vertex and an optional index buffer. 
* The typical creation cycle is: 
* * Creating a new instance of Mesh (which is useless on it's own)
* * Call `create` to create the underlying data structures
* * Call `prime` to obtain a HotMesh (the Mesh need to be created first)
*/
class Mesh : public config::CommonBase {
public:
  // default constructor
  Mesh();

  // Mesh(int vertexCount);
  // Mesh(int vertexCount, int indexCount);

  // copy constructor and copy assignment operator
  Mesh(const Mesh& copy);
  Mesh &operator=(const Mesh &copy);

  // move constructor and move assignment operator
  Mesh(Mesh&& m);
  Mesh& operator=(Mesh&& m);

  // destructor
  ~Mesh();

  void create(int vertexCount, int indexCount = 0);
  template <typename... Cs, typename L> void prime(L lambda);

  // tmp
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

  Mesh(Mesh& ref);

  void setPrimitiveType(PrimitiveType type);

  void bindAll();
  void unbindAll();

  static bool s_isPrimed;

  template <typename... Cs>
  friend class HotMesh;
};


/**
 * @brief Hot version of mesh
 * @details [long description]
 * 
 * @tparam Cs [description]
 */
template <typename... Cs>
class HotMesh : public Mesh {
private:
  HotMesh(Mesh& ref);

  friend Mesh;


public:
  // delete copy and move constructors to avoid copys
  HotMesh(const HotMesh&) = delete;
  HotMesh& operator=(const HotMesh&) = delete;
  HotMesh(HotMesh&&) = delete;
  HotMesh& operator==(HotMesh&&) = delete;

  // custom destructor
  ~HotMesh();

  // use functions of base class
  using Mesh::setPrimitiveType;
  void applyVertexLayout();

  internal::VBufferWriteHelper<Cs...> vertex;
  internal::IndexSet index;
};



// =============================================================================
// Definition of internal helper types
// =============================================================================
namespace internal {
/**
 * Type of the `vertex` member of a HotMesh. Overloads operator[] and executes
 * bound checks.
 */
template <typename... Cs>
struct VBufferWriteHelper {
private:
  // declare friends
  template <typename...> friend class ::lumina::HotMesh;

  // internal data
  void* buffer;
  int vertexCount;

public:
  VBufferWriteHelper(int vertexCount)
    : buffer(nullptr), vertexCount(vertexCount) {}

  // subscript operator
  AssignBufferWriter<Cs...> operator[](int index) {
    // Test if index is valid (not even asan detects overflow the memory 
    // after this block is somehow allocated by OpenGL anyways)
    if(index >= ((vertexCount*4)/internal::LayoutTypes<Cs...>::stride)) {
      throw GLException("VertexWriter: Index out of bounds!");
    }

    // calculate offset and return another helper object
    auto* buf = static_cast<char*>(buffer)
                + index * internal::LayoutTypes<Cs...>::stride;
    return AssignBufferWriter<Cs...>(buf);
  }    
};


/**
 * Helper for overloading the = operator. 
 */
template <typename T, typename... Ts> 
struct AssignBufferWriter {
private:
  void* buffer;

public:
  AssignBufferWriter(void* ptr) : buffer(ptr) {}

  CommaBufferWriter<Ts...> operator=(T data) {
    *static_cast<T*>(buffer) = data;
    return CommaBufferWriter<Ts...>(static_cast<T*>(buffer) + 1);
  }
};

// specialization for just one remaining type
template <typename T>
struct AssignBufferWriter<T> {
private:
  void* buffer;

public:
  AssignBufferWriter(void* ptr) : buffer(ptr) {}

  void operator=(T data) { *static_cast<T*>(buffer) = data; }
};


/**
 * Helper type for overloading the , operator.
 */
template <typename T, typename... Ts>
struct CommaBufferWriter {
private:
  void* buffer;

public:
  CommaBufferWriter(void* ptr) : buffer(ptr) {}

  CommaBufferWriter<Ts...> operator,(T data) {
    *static_cast<T*>(buffer) = data;
    return CommaBufferWriter<Ts...>(static_cast<T*>(buffer) + 1);
  }
};

// specialization for just one remaining type
template <typename T>
struct CommaBufferWriter<T> {
  private:
  void* buffer;

public:
  CommaBufferWriter(void* ptr) : buffer(ptr) {}

  void operator,(T data) {
    *static_cast<T*>(buffer) = data;
  }
};

} // namespace internal

} // namespace lumina

// include out of line definitions
#include "Mesh.tpp"