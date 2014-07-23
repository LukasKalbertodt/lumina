namespace lumina {

inline PerFragmentProcessing::PerFragmentProcessing()
  : m_depthEnabled(false),
    m_depthWrite(true),
    m_depthFunc(DepthFunction::Less) {}

inline void PerFragmentProcessing::enableDepthTest(bool enable) {
  m_depthEnabled = enable;
}
inline void PerFragmentProcessing::enableDepthWrite(bool enable) {
  m_depthWrite = enable;
}
inline void PerFragmentProcessing::setDepthFunction(DepthFunction func) {
  m_depthFunc = func;
}


}