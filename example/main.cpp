#include "lumina/video/LWindow.hpp"
#include "lumina/video/LDriverFactory.hpp"
#include "lumina/util/LVector.hpp"
#include "lumina/util/LMatrix.hpp"
#include "lumina/video/gl/LGLVertexBuffer.hpp"
#include "lumina/video/LRawMesh.hpp"

// #include <memory>
// #include <string>
// #include <functional>
#include <iostream>
#include <vector>

#include <GL/glew.h>

using namespace lumina;
using namespace std;



LEventResult onEvent(const LInputEvent& e) {
  // cout << "Event :)" << endl;
  if(e.type == LInputType::KeyInput &&
      e.keyInput.type == LKeyEventType::Character) {
    cout << e.keyInput.c << endl;
  }

  if(e.type == LInputType::MouseInput &&
      e.mouseInput.type == LMouseEventType::LButtonPressed) {
    cout << "LÄFT" << endl;
  }

  return LEventResult::Skipped;
}

void windowTest();


int main() {
  windowTest();

}

void windowTest() {
  bool run = true;

  LWindow win("Hai :3");
  win.setVersionHint(3, 3);
  auto a = win.addEventCallback(onEvent);
  // win.removsceEventCallback(a);
  win.addEventCallback([&](const LInputEvent& e) {
    if(e.keyInput.c == 'x') { 
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
  cout << screenSize << endl;


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

  // GLuint VertexArrayID;
  // glGenVertexArrays(1, &VertexArrayID);
  // glBindVertexArray(VertexArrayID);

  // cout << "VAO: " << VertexArrayID << endl;

  // LGLVertexBuffer buf;
  // buf.create(3, 12);
  // buf.copyData(vertexData, sizeof(vertexData));
  // auto handle = buf.getHandle();

  // glBindBuffer(GL_ARRAY_BUFFER, handle);
  // glVertexAttribPointer(
  //    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
  //    3,                  // size
  //    GL_FLOAT,           // type
  //    GL_FALSE,           // normalized?
  //    0,                  // stride
  //    (void*)0            // array buffer offset
  // );

  // glEnableVertexAttribArray(0);

  LRawMesh mesh;
  mesh.createVertexBuffer(9);
  mesh.fillVertexData(vertexData, sizeof(vertexData));
  // mesh.setVertexLayout(createVertexLayout<LVertexComponent::Pos3D>());
  mesh.setVertexLayout(createVertexLayout());

  while(win.isValid() && run) {
    win.update();


    // glEnableVertexAttribArray(0);
    
     
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
     
    // glDisableVertexAttribArray(0);

    // glBegin(GL_QUADS);
    //   glTexCoord2f(0.f, 1.f); glVertex2f(-0.5f, -0.5f);
    //   glTexCoord2f(1.f, 1.f); glVertex2f(1.f, -1.f);
    //   glTexCoord2f(1.f, 0.f); glVertex2f(1.f, 1.f);
    //   glTexCoord2f(0.f, 0.f); glVertex2f(-1.f, 1.f);
    // glEnd();

    // glBegin(GL_QUADS);
    //   glVertex2f(-0.5f, -0.5f);
    //   glVertex2f(1.f, -1.f);
    //   glVertex2f(1.f, 1.f);
    //   glVertex2f(-1.f, 1.f);
    // glEnd();

    cnt->swapBuffer();
  }
}