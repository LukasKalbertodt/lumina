#pragma once

#include "../config/BaseProxy.hpp"
#include "LShader.hpp"

#include <GL/glew.h>

namespace lumina {

class PipelineContainer : public config::CommonBase {
public:
  PipelineContainer(LShader<LShaderType::Vertex>& vs,
                     LShader<LShaderType::Fragment>& fs)
    : m_vertexShader(vs), m_fragmentShader(fs), m_program(0) {
    linkShaderProgram();
  }

  // TEMP!
  void use();


private:
  LShader<LShaderType::Vertex>& m_vertexShader;
  LShader<LShaderType::Fragment>& m_fragmentShader;
  GLuint m_program;

  void linkShaderProgram();
};


// PipelineContainer linkPipeline()




} // namespace lumina