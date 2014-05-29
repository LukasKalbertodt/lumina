#pragma once

#include "HotMesh.fpp"
#include "IndexSet.hpp"
#include "Mesh.hpp"
#include "PrimitiveType.hpp"
#include "VertexSet.hpp"
#include "../config/BaseProxy.hpp"


namespace lumina {

/**
 * @brief Hot version of mesh
 * @details [long description]
 * 
 * @tparam Cs [description]
 */
template <typename... Cs>
class HotMesh : public config::CommonBase{
private:
  Mesh& m_mesh;

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

  void setPrimitiveType(PrimitiveType type);
  void applyVertexLayout();

  internal::VertexSet<Cs...> vertex;
  internal::IndexSet index;
};

} // namespace lumina

#include "HotMesh.tpp"