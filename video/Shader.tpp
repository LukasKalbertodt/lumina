namespace lumina {

template <ShaderType Type>
Shader<Type>::Shader() : m_handle(0) {}

template <ShaderType Type>
GLuint Shader<Type>::getHandle() const { return m_handle; }
template <ShaderType Type>
std::string Shader<Type>::getFilename() const { return m_filename; }

template <ShaderType Type>
void Shader<Type>::compile(std::string code) {
  compile(ShaderSource(code, "unknown-file"));
}

}