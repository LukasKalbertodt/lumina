#include "lumina/lumina.hpp"
#include "lumina/util/Color.hpp"

#include <iostream>
#include <vector>

using namespace lumina;
using namespace std;

void windowTest();

int main() {
  windowTest();
}

void windowTest() {
  bool run = true;

  LWindow win("Hai :3");
  win.setVersionHint(3, 3);
  win.setVSync(true);
  // win.setVersionHint(1, 1);
  win.addEventCallback([&](const LInputEvent& e) {
    if(e.keyInput.key == LKeyCode::Escape) { 
      run = false; 
      return LEventResult::Processed;
    }
    return LEventResult::Skipped;
  });
  win.open();
  win.setVSync(true);

  auto cnt = win.getRenderContext();
  cnt->create();
  cnt->makeCurrent();



  LMesh mesh(3*3*2);
  
  mesh.apply<Vec3f, Color32f>([](auto& m) {
    m.vertex[0] = Vec3f(-1.f, -1.f, 0.f), Color32f(1.f, 0.f, 0.f);
    m.vertex[1] = Vec3f(1.f, -1.f, 0.f), Color32f(0.f, 1.f, 0.f);
    m.vertex[2] = Vec3f(0.f, 1.f, 0.f), Color32f(0.f, 0.f, 1.f);
    m.applyVertexLayout();
  });


  // Shader tests
  LShader<LShaderType::Vertex> vs;
  vs.compile(loadShaderFromFile("shader/test.vsh"));
  LShader<LShaderType::Fragment> fs;
  fs.compile(loadShaderFromFile("shader/test.fsh"));
  LPipelineContainer p(vs, fs);
  p.use();

  while(win.isValid() && run) {
    win.update();    
     
    // Draw the triangle !
    // glDrawArrays(GL_TRIANGLES, 0, 3); 
    mesh.sendData();

    cnt->swapBuffer();
  }
}