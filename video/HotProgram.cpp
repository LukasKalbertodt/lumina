#include "HotProgram.hpp"
#include "GLException.hpp"
#include "VertexSeq.hpp"

#include <vector>
using namespace std;

namespace lumina {

bool HotProgram::s_isPrimed = false;


void HotProgram::draw(const VertexSeq& data,
                      PrimitiveType type,
                      int offset,
                      int count) {
  data.bindVAO();

  if(count == -1) {
    count = data.size();
  }

  GLenum primitiveType = translatePrimitiveType(type);
  if(data.nativeIndexHandle() == 0) {
    glDrawArrays(primitiveType, offset, count);
  }
  else {
    glDrawElements(primitiveType, count, GL_UNSIGNED_INT,
                   reinterpret_cast<void*>(4 * offset));
  }
  data.unbindVAO();
}




}