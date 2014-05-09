#include "lumina/video/LWindow.hpp"
// #include "lumina/video/LDriverFactory.hpp"
#include "lumina/util/LVector.hpp"
#include "lumina/util/LMatrix.hpp"
#include "lumina/video/gl/LGLVertexBuffer.hpp"
#include "lumina/video/LRawMesh.hpp"
#include "lumina/video/LShader.hpp"
#include "lumina/video/LShaderSource.hpp"

// #include <memory>
// #include <string>
// #include <functional>
#include <iostream>
#include <vector>

#include <GL/glew.h>

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
  win.addEventCallback([&](const LInputEvent& e) {
    if(e.keyInput.key == LKeyCode::Escape) { 
      run = false; 
      return LEventResult::Processed;
    }
    return LEventResult::Skipped;
  });
  win.open();

  auto cnt = win.getRenderContext(LDriverType::OpenGL);
  cnt->create();
  cnt->makeCurrent();


  auto screenSize = win.getSize();
  cout << "Resolution: " << screenSize << endl;


  // Shader tests
  LShader<LShaderType::Vertex> vs;
  vs.compile(loadShaderFromFile("shader/test.vsh"));
  LShader<LShaderType::Fragment> fs;
  fs.compile(loadShaderFromFile("shader/test.fsh"));









  // GLuint texColor, texNormal;
  // glGenTextures(1, &texColor);
  // glBindTexture(GL_TEXTURE_2D, texColor);
  // //<texture params>
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screenSize.x, screenSize.y,
  //              0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  // // glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
  // //                           GL_TEXTURE_2D, texColor, 0);

  // glGenTextures(1, &texNormal);
  // glBindTexture(GL_TEXTURE_2D, texNormal);  

  // vector<uint32_t> texData(screenSize.x * screenSize.y);
  // for(int x = 0; x < screenSize.x; x++) {
  //   for(int y = 0; y < screenSize.y; y++) {
  //     // cout << x*screenSize.x + y << endl;
  //     texData[x*screenSize.y + y] = 0xFFFFFFFF;
  //   }
  // }

//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, screenSize.x, screenSize.y,
//                0, GL_RGBA, GL_UNSIGNED_BYTE, texData.data());
//   // glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
//   //                           GL_TEXTURE_2D, texNormal, 0);


//   glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

  // static const float vertexData[] = {
  //   -0.5f, -0.5f, 0.0f, 
  //   1.0f,  -1.0f, 0.0f, 
  //   1.0f,  1.0f,  0.0f,
  // };

  static const float vertexData[] = {
     -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f,
  };


  LRawMesh mesh;
  mesh.createVertexBuffer(9);
  mesh.fillVertexData(vertexData, sizeof(vertexData));
  mesh.setVertexLayout(createVertexLayout());

  while(win.isValid() && run) {
    win.update();    
     
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); 

    cnt->swapBuffer();
  }
}