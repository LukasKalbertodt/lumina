#pragma once

#include "VertexSeq.fpp"
#include "VertexLayout.hpp"
#include "HotVertexSeq.fpp"
#include "HotProgram.fpp"
#include "GLObject.hpp"
#include "../config/BaseProxy.hpp"

#include <GL/glew.h>
#include <cstddef>
#include <memory>
#include <iostream>


namespace lumina {

namespace internal {

class VertexSeqBase : public GLObject {
public:
  // ===== constructor, destructor, assignment-operator =====
  VertexSeqBase();
  VertexSeqBase(const VertexSeqBase&) = delete;
  VertexSeqBase(VertexSeqBase&& m) noexcept;

  ~VertexSeqBase();

  VertexSeqBase& operator=(VertexSeqBase m);


  // ===== public methods =====
  /// Returns the native OpenGL handle of the vertex buffer
  GLuint nativeVertexHandle() const;

  /// Returns the native OpenGL handle of the index buffer
  GLuint nativeIndexHandle() const;

  /// Returns the native OpenGL handle of the vertex array object
  GLuint nativeVAOHandle() const;

  /// Returns the number of vertices
  uint32_t vertexCount() const;

  /// Returns the number of indicies
  uint32_t indexCount() const;

  /// Returns the number of vertices in the sequence
  int size() const;

  /// Determines if a vertex layout is active
  bool isLayoutActive() const;

  /// Returns true if the VertexSeq was created
  explicit operator bool() const;

  static void setupOpenGL();

protected:
  // ===== protected member =====
  GLuint m_vertexHandle;
  GLuint m_indexHandle;
  GLuint m_vertexArrayObject;
  uint32_t m_vertexCount;
  uint32_t m_indexCount;
  bool m_layoutActive;

  static bool s_isPrimed;


  // ===== protected methods =====
  void bindAll();
  void unbindAll();

  void bindVAO() const;
  void unbindVAO() const;

  void create(uint16_t vertexSize, uint32_t vertexCount, uint32_t indexCount);


  // ===== friend declarations =====
  friend internal::HotVertexSeqBase;
  friend HotProgram;
};

} // namespace internal



// =============================================================================
// Definition of VertexSeq
// =============================================================================
/** Represents a sequence of vertices.
* VertexSeq represents a sequence of vertices with arbitrary attributes, which 
* may be indexed. It uses an OpenGL vertex buffer and an optional index buffer.
*  
* The typical creation cycle is: 
* * Creating a new instance of VertexSeq (which is useless on it's own)
* * Call `create` to create the underlying data structures
* * Call `prime` to obtain a HotVertexSeq (the VertexSeq needs to be 
* created first)
*
* \see HotVertexSeq
* \see HotVertexSeq<>
*/
template <typename... Ts>
class VertexSeq : public internal::VertexSeqBase {
public:
  /** Creates internal data structures.
   * Creates a OpenGL vertex buffer (VBO), a vertex array object (VAO),
   * and an optional index buffer when indexCount is not 0.
   * \note You cannot call this while another VertexSeq is primed!
   * 
   * @param vertexSize The size of one vertex in number of GLfloats. If your
   * vertex contains just a position of three floats (x,y,z) the size is 3.
   * @param vertexCount The number of vertices this sequence should hold. If 
   * you want to represent a triangle, you need 3 vertices.
   * @param indexCount The number of indicies in the index buffer (0 if you
   * don't need an index buffer)
   */
  void create(uint32_t vertexCount, uint32_t indexCount = 0);

  /** Primes the VertexSeq to obtain a HotVertexSeq.
  * Binds all OpenGL resources in order to use (writing data) the VertexSeq.
  * \note You cannot call prime while another VertexSeq is primed!
  *
  * \param lambda A functor that accepts a HotVertexSeq& as parameter. It will 
  * be called after the HotVertexSeq is created.
  * \tparam Cs A list of types of which a vertex consists. If your vertices 
  * contain a 3D-Position and a 2D-UV-Coordinate, use those 
  * templates: Vec3f, Vec2f
  */
  // template <typename L>
  // void prime(L lambda);

  /** Primes the VertexSeq to obtain a HotVertexSeq.
  * Binds all OpenGL resources in order to use (writing data) the VertexSeq.
  * This is the type-unsafe overload of prime. Whenever you can, you should 
  * use the type-safe variant.
  * \note You cannot call prime while another VertexSeq is primed!
  *
  * \param func A functor that accepts a HotVertexSeq<>& as parameter. It will 
  * be called after the HotVertexSeq is created.
  */
  void prime(std::function<void(HotVertexSeq<Ts...>&)> func);
};

} // namespace lumina

// include out of line definitions
#include "VertexSeq.tpp"