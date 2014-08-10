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
- __modern__: Use C++11 features where it's appropriate (Maybe using C++14 features 
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
Want to jump right into lumina? Start with the following guides to learn the 
basics:
- \ref s_window
- \ref s_vertexseq


\page config Configuration
Coming soon...

\page s_window Open a window and creating a context
A window is necessary for most things in lumina. This is always the first step
when creating an application.

The class \ref lumina::Window "Window" represents a window. Before we can open
the window we need to configure some aspects. One important thing is to give
a OpenGL version hint. Without this hint OpenGL doesn't know which version to
use. It's called "hint" for a reason: The implementation can ignore the hint 
and use another version. Most of the time OpenGL tries to match the hint as
best as possible. If we use a version that is too old, we may not have all
features we need. If we use a version that is too new, it can happen that our
hardware does not support all features of the requested version and the context
creation will fail. Currently lumina uses just OpenGL 3.3 features. So we go 
with 3.3 for now.

Our first code looks like this:
\code
Window win("My first application");
win.setVersionHint(3, 3);
win.resize(Vec2i(600, 400));
\endcode

We have specified a version hint, window size and title. Now we are ready to
open the window:
\code
win.open()
\endcode

The next step is to obtain the render context from our window. OpenGL needs a
render context in order to do anything. Therefore we cannot use most of the
OpenGL classes until we have context. Obtaining the context is easy, but we
also need to create the context:
\code
auto& renderContext = win.getRenderContext();
renderContext.create();
\endcode

Our render context is ready now. But to use it, we have to prime it. In most
cases we only have one render context and all of the other application uses
this context. So it's clever to prime the context just once and pass a function
to prime() that does everything else in the application. Lets call that
function "runGame".
\code
renderContext.prime(runGame);
\endcode


With this basic setup we can move on to actually do something. Maybe continue
with \ref s_vertexseq ?


\see \ref lumina::RenderContext "RenderContext"
\see \ref lumina::Window "Window"



\page s_vertexseq Create a VertexSeq

Vertices are the data that is processed by the OpenGL pipeline. So we need
vertices to draw anything. VertexSeq helps us with that by providing a easy
way to manage a set of vertices with a given order. The order is important,
because it determines how OpenGL interprets the data. You have two 
possibilities to give vertices an order:
- Do nothing: If you just specify vertices, the order is the same as the order
in which those vertices lay in the memory
- Use an index buffer: The index buffer is a clever tool to save memory, 
because you don't have to specify any vertex twice. For more information about
index buffers see somewhere else.

Note: This tutorial won't cover how to draw a VertexSeq, but just to fill it.

First we want to create a simple triangle. A triangle has 3 vertices. Our 
vertices just need a position on the screen (x,y -> 2 floats). Our code looks
like that:
\code
VertexSeq triangle;
triangle.create(2, 3);
\endcode

Now we have created all necessary buffers for our triangle. We just need to 
fill in the data. In order to do so we have to prime our VertexSeq. We need to
pass some template arguments to prime, because it want to know how our vertex
looks like. We said that we just need a screen position, so our vertex consists
just of a Vec2f. We also pass a lambda to prime.

In the lambda we do the main work. We write some data (the screen position)
to the buffer.
\code
triangle.prime<Vec2f>([](HotVertexSeq& hotTri) {
  hotTri.vertex[0] = Vec2f(0.5f, 0.f);
  hotTri.vertex[1] = Vec2f(0.f, 1.f);
  hotTri.vertex[2] = Vec2f(1.f, 1.f);
});
\endcode

The sequence is ready for drawing now. 

What if we wanted to create a quad instead of a triangle? We need 4 vertices
for the quad. But to draw them we need an index buffer specify an order. 
Let's suppose we want to draw with the primitive type Triangle (and not 
TriangleStrip). We then need 6 indicies to define 2 triangles. The size of one
vertex hasn't changed. Our new code:
\code
VertexSeq quad;
quad.create(2, 4, 6);

quad.prime<Vec2f>([](HotVertexSeq& hotQuad) {
  hotQuad.vertex[0] = Vec2f(0.f, 0.f);
  hotQuad.vertex[1] = Vec2f(1.f, 0.f);
  hotQuad.vertex[2] = Vec2f(1.f, 1.f);
  hotQuad.vertex[3] = Vec2f(0.f, 1.f);

  hotQuad.index[0] = 0;
  hotQuad.index[1] = 2;
  hotQuad.index[2] = 1;
  hotQuad.index[3] = 0;
  hotQuad.index[4] = 1;
  hotQuad.index[5] = 3;
});
\endcode

Note: You should pay attention to the winding order. 


\see \ref lumina::VertexSeq "VertexSeq"
\see \ref lumina::HotVertexSeq "HotVertexSeq"


*/