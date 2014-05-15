#include "lumina/lumina.hpp"

#include <iostream>
#include <vector>

using namespace lumina;
using namespace std;


int main() {
  // ===========================================================================
  // Open window and create context
  // ===========================================================================
  // helper variable to close window with ESC
  bool run = true;

  // create window with openGL version 3.3
  LWindow win("Colored triangle with lumina! :3");
  win.setVersionHint(3, 3);

  // set run to false if ESC is pressed -> close the program
  win.addEventCallback([&](const LInputEvent& e) {
    if(e.keyInput.key == LKeyCode::Escape) { 
      run = false; 
      return LEventResult::Processed;
    }
    return LEventResult::Skipped;
  });

  // open window and enable vsync
  win.open();
  win.setVSync(true);

  // obtain render context and make it current
  auto cnt = win.getRenderContext();
  cnt->create();
  cnt->makeCurrent();



  // ===========================================================================
  // Create Mesh and shaders
  // ===========================================================================
  // mesh data: 3 floats position, 3 floats color
  static const float vertexData[] = {
     -1.0f, -1.f, 0.0f, 1.0f, 0.f, 0.f,
     1.0f, -1.0f, 0.0f, 0.f, 1.f, 0.f,
     0.0f,  1.0f, 0.0f, 0.f, 0.f, 1.f
  };

  // create mesh and load data into mesh
  LMesh mesh;
  mesh.createVertexBuffer(sizeof(vertexData)/4);
  mesh.fillVertexData(vertexData, sizeof(vertexData));

  // set the buffer layout
  mesh.setVertexLayout(
    createVertexLayout<LVertexComponent::Pos3D, LVertexComponent::Color>());

  // create and compile two shaders 
  LShader<LShaderType::Vertex> vs;
  vs.compile(loadShaderFromFile("shader/test.vsh"));
  LShader<LShaderType::Fragment> fs;
  fs.compile(loadShaderFromFile("shader/test.fsh"));

  // create a pipeline that links the shaders
  LPipelineContainer p(vs, fs);
  p.use();



  // ===========================================================================
  // Run until ESC is pressed or the window should close
  // ===========================================================================
  while(win.isValid() && run) {
    // update window (poll events...)
    win.update();    
     
    // Draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); 

    // swap buffers
    cnt->swapBuffer();
  }
}