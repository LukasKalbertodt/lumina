#pragma once
#include "LShader.hpp"
#include "Program.fpp"
#include "RenderContext.fpp"
#include "UniformSet.hpp"
#include "../config/BaseProxy.hpp"

#include <GL/glew.h>
#include <string>

namespace lumina {

class Program : public config::CommonBase, public NonCopyable {
public:
  Program();

  void link(LShader<LShaderType::Vertex> vs, LShader<LShaderType::Fragment> fs);

  // TMP
  void use() { glUseProgram(m_program); }

protected:
  Program(Program& ref);

  GLuint m_program;
};

class HotProgram : public Program {
public:
  internal::UniformSet uniform;

  ~HotProgram();

private:
  HotProgram(Program& ref);

  friend RenderContext;
};

}

#include "Program.tpp"