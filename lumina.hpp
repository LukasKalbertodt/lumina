#pragma once

// include config
#include "config/LConfig.hpp"

// include core components
#include "core/LuminaException.hpp"

// include input components
#include "input/KeyCode.hpp"
#include "input/InputEvent.hpp"

// include utility types
#include "util/util.hpp"

// include video.hpp -> includes more files
#include "video/video.hpp"

#include "scene/scene.hpp"

#include "io/Image.hpp"


// namespace alias
namespace lum = lumina;




/*!
\mainpage Introduction
Lumina is a C++ OpenGL graphics library with the following design principles:
- __lightweight__: Just provide features which are necessary
- __modern__: Use C++11 features where it's appropriat (Maybe using C++14 features 
in future versions)
- __render-pipeline-abstraction__: Make it easy to use the OpenGL pipeline but 
don't provide high level functions like game engines would
- __little-to-zero-overhead__: Don't do anything that the user may not want to do

This is the first working release of lumina and there is a lot more work to 
do. Everything can change in newer versions. The first major version (1.0) 
will have a fixed API that won't change anymore.


## How to start
There are the following guides for different areas:
- \ref getting_started "Getting Started"
- \ref important_classes "A collection of important classes"
- \ref config "Configuration"


\page important_classes Important classes
\section opengl OpenGL
- \ref lumina::VertexSeq "VertexSeq" - Represents a sequence of vertices 
- \ref lumina::Window "Window" - A window with OpenGL context
- \ref lumina::Shader "Shader" - Vertex or Fragment Shader
- \ref lumina::Program "Program" - All stages of the OpenGL pipeline
- \ref lumina::FrameBuffer "FrameBuffer" - Container for render targets
- \ref lumina::Texture "Texture" - A OpenGL texture
- \ref lumina::RenderContext "RenderContext" - The OpenGL render context

\section imp_util Utilities
- \ref lumina::Vector "Vector"
- \ref lumina::Matrix "Matrix"
- \ref lumina::Matrix "Quaternion"
- \ref lumina::Color "Color"
- \ref lumina::half "half"

\page getting_started Getting Started
blagsdf


\page config Configuration
dfsdf
*/