#pragma once
#include "GLObject.hpp"
#include "Program.fpp"
#include "RenderContext.fpp"
#include "Shader.hpp"
#include "UniformSet.hpp"
#include "../config/BaseProxy.hpp"

#include <GL/glew.h>
#include <functional>
#include <string>

namespace lumina {

class Program : public GLObject {
public:
  Program();
  ~Program();

  void create(VShader& vs, FShader& fs);
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