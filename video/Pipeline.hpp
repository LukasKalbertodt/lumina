#pragma once

#include "../config/BaseProxy.hpp"
#include "Shader.hpp"

#include <GL/glew.h>

namespace lumina {

class PipelineContainer : public config::CommonBase {
public:
  PipelineContainer(Shader<ShaderType::Vertex>& vs,
                     Shader<ShaderType::Fragment>& fs)
    : m_vertexShader(vs), m_fragmentShader(fs), m_program(0) {
    linkShaderProgram();
  }

  // TEMP!
  void use();


private:
  Shader<ShaderType::Vertex>& m_vertexShader;
  Shader<ShaderType::Fragment>& m_fragmentShader;
  GLuint m_program;

  void linkShaderProgram();
};


// PipelineContainer linkPipeline()




} // namespace lumina