#pragma once
#include "Program.fpp"
#include "Shader.hpp"
#include "RenderContext.fpp"
#include "UniformSet.hpp"
#include "../config/BaseProxy.hpp"

#include <GL/glew.h>
#include <functional>
#include <string>

namespace lumina {

class Program : public config::CommonBase, public NonCopyable {
public:
  Program();
  ~Program();

  void create(VShader vs, FShader fs);
  void prime(std::function<void(HotProgram&)> func);

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

  static bool s_isPrimed;

  friend Program;
};

}

#include "Program.tpp"