namespace lumina {

inline HotProgram::HotProgram(Program& ref) : uniform(ref.m_handle) {}


template <typename... Ts>
void HotProgram::draw(const HotTexCont& texCont,
                      const VertexSeq<Ts...>& data,
                      PrimitiveType type,
                      int offset,
                      int count) {
  // if textures are used, we need to check the number of textures in the 
  // texture container against the number of currently primed textures
  if(config::debugTextureDrawChecks) {
    if(texCont.count() != TextureUnits::countPrimed()) {
      logThrowGL("[HotProgram] Trying to draw with TextureContainer that "
                 "contains <", texCont.count(), "> textures, but <",
                 TextureUnits::countPrimed(), "> are currently primed!");
    }
  }

  // draw
  drawImpl(data, type, offset, count);
}

template <typename... Ts>
void HotProgram::draw(const VertexSeq<Ts...>& data,
                      PrimitiveType type,
                      int offset,
                      int count) {
  // calling draw without texture container -> user don't want to use textures
  // -> we need to make sure, none are primed
  if(config::debugTextureDrawChecks) {
    if(TextureUnits::countPrimed()) {
      logThrowGL("[HotProgram] Trying to draw without a TextureContainer, "
                 "but <", TextureUnits::countPrimed(), "> textures are "
                 "currently primed!");
    }
  }

  // draw
  drawImpl(data, type, offset, count);
}

template <typename... Ts>
void HotProgram::drawImpl(const VertexSeq<Ts...>& data,
                          PrimitiveType type,
                          int offset,
                          int count) {
  // check if any FrameBuffer is bound
  if(config::debugDrawFrameBufferCheck) {
    if(!FrameBuffer::isPrimed()) {
      logThrowGL("[HotProgram] Attempt to call draw without a primed "
                 "framebuffer! (forgot to prime the default FrameBuffer?)");
    }
  }

  if(!data.isVertexLayoutActive()) {
    logThrowGL("[HotProgram] Attempt to call draw with a VertexSeq whose is "
               "not active! (forgot to call applyVertexLayout?)");
  }

  // bind vertex and index data
  data.bindVAO();

  // if the count parameter was not supplied, we use the whole sequence
  if(count == -1) {
    count = data.size();
  }

  // get the GL type
  GLenum primitiveType = translatePrimitiveType(type);

  // if there is no index buffer -> use glDrawArrays, glDrawElements otherwise
  if(data.nativeIndexHandle() == 0) {
    glDrawArrays(primitiveType, offset, count);
  }
  else {
    glDrawElements(primitiveType, count, GL_UNSIGNED_INT,
                   reinterpret_cast<void*>(sizeof(GLuint) * offset));
  }

  // unbind vertex and index data
  if(config::resetGLState) {
    data.unbindVAO();
  }
}

}