namespace lumina {

inline PrimitiveProcessing::PrimitiveProcessing()
  : m_frontFace(constants::DefaultFrontFace),
    m_cullFace(constants::DefaultCullFace),
    m_cullEnable(constants::DefaultCullEnable) {}

inline void PrimitiveProcessing::enableCulling(bool enable) {
  m_cullEnable = enable;
}


inline void PrimitiveProcessing::setFrontFace(FaceOrder order) {
  m_frontFace = order;
}

inline void PrimitiveProcessing::setCullFace(CullFace face) {
  m_cullFace = face;
}

}