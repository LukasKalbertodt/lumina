#include "lumina/video/LWindow.hpp"
#include "lumina/video/LDriverFactory.hpp"
#include "lumina/util/LVector.hpp"
#include "lumina/util/LMatrix.hpp"
#include "lumina/video/gl/LGLVertexBuffer.hpp"

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
void vectorTest();
void matrixTest();


int main() {
  windowTest();
  // vectorTest();
  // matrixTest();

  // cout << +static_cast<uint8_t>(300.f) << endl;

  // Color8 c1(255, 255, 0);
  // cout << c1 << endl;
  // cout << createColorHexCode(c1) << endl;
  // cout << makeColor<Color8>(0.5f, 0.2f, 1.f) << endl;
  // cout << colorToVec(makeColor<Color8>(0.5f, 0.2f, 1.f)) << endl;
  // cout << colorToVec3f(c1) << endl;





  // LVector<float, 3> v1(1,2,3);
  // LVector<float, 3> v2(6.1f,7.2f,8.3f);
  // v1 += v2;
  // cout << v1 << endl;
  // cout << v2 << endl;
  // cout << v1.x << "," << v1.z << endl;

  // cout << LVector<float, 5>(11, 12, 13, 44, 109) << endl;
  // cout << LVector<float, 2>(0.f, 1.5f) + LVector<int, 2>(0, 1) << endl;

  // cout << "cast to int: " << vector_cast<int>(v2) << endl;
  // cout << "cast to 2d:  " << vector_cast<2>(v2) << endl;
  // cout << "cast to 4di: " << vector_cast<int, 4>(v2) << endl;

  

  // LWindow win2("Doppelgänger!");
  // // win2.open();
  // // auto con = win.getRenderContext(LDriverType::OpenGL);

  // // LDriverFactory f(LDriverType::OpenGL);
  // // auto s = f.make<LShader>();
  // // s->compile();

  // while(run && (win.isValid() || win2.isValid())) {
  //   win.update();
  //   win2.update();
  // }
}


void matrixTest() {
  LMatrix<float, 4, 4> m1;
  m1.setToIdentity();
  m1.data[0][3] = 2.f;
  cout << m1 << endl;
  cout << -m1.inverted() << endl;
  cout << m1.determinant() << endl;
  cout << m1.getDiagonal() << endl;
  cout << Mat4f() - m1 << endl;
  cout << m1 * m1 << endl;
  cout << matrix_cast<MatQf<5>>(m1) << endl;

  Vec4f vec(1,2,3,4);
  cout << m1 * vec << endl;


  Mat2f m2;
  cout << m2.determinant() << endl;
}



void vectorTest() {
  asm("# MARK0");
  Vec2i dim{2, 4};

  asm("# MARK1");
  std::vector<uint32_t> data(dim.linearSize());
  asm("# MARK2");

  auto it = begin(dim);
  asm("# MARK2");

  auto e = end(dim);
  asm("# MARK2");

  // ++it;
  asm("# MARK2");
  asm("# MARK2");
  asm("# MARK2");


  while(it != e) {
    // data[*it] = it.x + it.y;
    ++it;
  }

  asm("# MARK2");
  asm("# MARK2");
  asm("# MARK2");
  asm("# MARK2");
  asm("# MARK2");
  asm("# MARK2");

  // for(auto index : dim) {
  //   cout << data[index] << endl;
  // }
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

  static const float vertexData[] = {
    -1.0f, -1.0f, 0.0f, 
    1.0f,  -1.0f, 0.0f, 
    0.0f,  1.0f,  0.0f,
  };

  LGLVertexBuffer buf;
  buf.create(3, 12);
  buf.copyData(vertexData, sizeof(vertexData));




  while(win.isValid() && run) {
    win.update();

    // glEnableVertexAttribArray(0);
    // glBindBuffer(GL_ARRAY_BUFFER, buf);
    // glVertexAttribPointer(
    //    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    //    3,                  // size
    //    GL_FLOAT,           // type
    //    GL_FALSE,           // normalized?
    //    0,                  // stride
    //    (void*)0            // array buffer offset
    // );
     
    // // Draw the triangle !
    // glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
     
    // glDisableVertexAttribArray(0);

    // glBegin(GL_QUADS);
    //   glTexCoord2f(0.f, 1.f); glVertex2f(-0.5f, -0.5f);
    //   glTexCoord2f(1.f, 1.f); glVertex2f(1.f, -1.f);
    //   glTexCoord2f(1.f, 0.f); glVertex2f(1.f, 1.f);
    //   glTexCoord2f(0.f, 0.f); glVertex2f(-1.f, 1.f);
    // glEnd();

    cnt->swapBuffer();
  }
}