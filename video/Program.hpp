#pragma once
#include "GLObject.hpp"
#include "Program.fpp"
#include "HotProgram.fpp"
#include "RenderContext.fpp"
#include "Shader.hpp"
#include "PrimitiveProcessing.hpp"
#include "PerFragmentProcessing.hpp"
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

  PrimitiveProcessing primitiveProc;
  PerFragmentProcessing perFragProc;

protected:
  Program(Program& ref);

  GLuint m_handle;

  friend HotProgram;
};

}

#include "Program.tpp"