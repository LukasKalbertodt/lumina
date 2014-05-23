#pragma once

namespace lumina {

enum class ShaderType { Vertex, Fragment };

template <ShaderType Type> class Shader;

// typedefs 
using VShader = Shader<ShaderType::Vertex>;
using FShader = Shader<ShaderType::Fragment>;

} // namespace lumina