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

/** Represents the configuration of an OpenGL pipeline.
It contains all important stages of the OpenGL Pipeline:
- Programmable: VertexShader, FragmentShader 
- Configureable: PrimitiveProcessing, PerFragmentProcessing

The vertex and fragment shader are neccessary to create a valid Program. To use
the Program you have to prime it.

\see HotProgram
*/
class Program : public GLObject {
public:
  Program();
  ~Program();

  /** Links the shaders and creates the Program.
  \note Both shaders need to be already compiled!

  \param vs vertex shader
  \param fs fragment shader
  */
  void create(VShader& vs, FShader& fs);

  /** Primes the Program in order to use it.
  Binds the program and applies all attributes of the configurable pipline
  stages. You need a HotProgram to draw something.

  \param func A functor that accepts a HotProgram& as parameter
  */
  void prime(std::function<void(HotProgram&)> func);

  /// PrimitiveProcessing pipeline stage
  PrimitiveProcessing primitiveProc;

  /// PerFragmentProcessing pipeline stage
  PerFragmentProcessing perFragProc;

protected:
  static bool s_isPrimed;

  GLuint m_handle;

  friend HotProgram;
};

}

#include "Program.tpp"