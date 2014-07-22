#pragma once

#include <GL/glew.h>

namespace lumina {

#define PROPS\
  X(MaxColorAttachments, int, GL_MAX_COLOR_ATTACHMENTS)\
  X(MaxColorTextureSamples, int, GL_MAX_COLOR_TEXTURE_SAMPLES)\
  X(MaxDepthTextureSamples, int, GL_MAX_DEPTH_TEXTURE_SAMPLES)\
  X(MaxDrawBuffers, int, GL_MAX_DRAW_BUFFERS)\
  X(MaxDualSourceDrawBuffers, int, GL_MAX_DUAL_SOURCE_DRAW_BUFFERS)\
  X(MaxFramebufferHeight, int, GL_MAX_FRAMEBUFFER_HEIGHT)\
  X(MaxFramebufferLayers, int, GL_MAX_FRAMEBUFFER_LAYERS)\
  X(MaxFramebufferSamples, int, GL_MAX_FRAMEBUFFER_SAMPLES)\
  X(MaxFramebufferWidth, int, GL_MAX_FRAMEBUFFER_WIDTH)\
  X(MaxIntegerSamples, int, GL_MAX_INTEGER_SAMPLES)\
  X(MaxSamples, int, GL_MAX_SAMPLES)\
  X(MaxAtomicCounterBufferSize, int, GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE)\
  X(MaxCombinedShaderOutputResources, int, GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES)\
  X(MaxCombinedShaderStorageBlocks, int, GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS)\
  X(MaxImageSamples, int, GL_MAX_IMAGE_SAMPLES)\
  X(MaxImageUnits, int, GL_MAX_IMAGE_UNITS)\
  X(MaxProgramTexelOffset, int, GL_MAX_PROGRAM_TEXEL_OFFSET)\
  X(MaxSubroutines, int, GL_MAX_SUBROUTINES)\
  X(MaxSubroutineUniformLocations, int, GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS)\
  X(MaxUniformBlockSize, int, GL_MAX_UNIFORM_BLOCK_SIZE)\
  X(MaxUniformLocations, int, GL_MAX_UNIFORM_LOCATIONS)\
  X(MaxVaryingVectors, int, GL_MAX_VARYING_VECTORS)\
  X(MaxVertexAttribRelativeOffset, int, GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET)\
  X(MaxVertexAttribBindings, int, GL_MAX_VERTEX_ATTRIB_BINDINGS)\
  X(MaxVertexAttribStride, int, GL_MAX_VERTEX_ATTRIB_STRIDE)\
  X(MaxCombinedTextureImageUnits, int, GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)




// define enum
#define X(name_, type_, gl_) name_,
enum class GLProp { PROPS NUM };
#undef X

// define helper functions
#define X(name_, type_, gl_) case GLProp::name_: return gl_;
inline GLenum translateGLProp(GLProp prop) { 
  switch(prop) { 
    PROPS 
    default: return GL_INVALID_ENUM; 
  } 
}
#undef X

#define X(name_, type_, gl_) case GLProp::name_: return #gl_;
inline const char* getGLPropName(GLProp prop) {
  switch(prop) { 
    PROPS 
    default: return "???"; 
  } 
}
#undef X

}