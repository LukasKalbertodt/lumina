namespace lumina {

inline PerFragmentProcessing::PerFragmentProcessing()
  : blendFuncRGB(BlendFunction::Add),
    blendFuncA(BlendFunction::Add),
    srcRGBParam(BlendParam::One),
    dstRGBParam(BlendParam::Zero),
    srcAParam(BlendParam::One),
    dstAParam(BlendParam::Zero),
   m_depthEnabled(false),
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

// inline void PerFragmentProcessing::setBlendFunction(BlendFunction funcRGB, BlendFunction funcA) {
//   m_blendFuncRGB = funcRGB;
//   m_blendFuncA = funcA;
// }

// inline void PerFragmentProcessing::setBlendParamsRGB(BlendParam src, BlendParam dst) {
//   m_srcRGBParams = src;
//   m_dstRGBParams = dst;
// }

// inline void PerFragmentProcessing::setBlendParamA(BlendParam src, BlendParam dst) {
//   m_srcAParams = src;
//   m_dstAParams = dst;
// }


}