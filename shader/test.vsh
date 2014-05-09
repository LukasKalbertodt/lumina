#version 330 core

layout(location = 0) in vec3 pos3D;

void main() {
  gl_Position.xyz = pos3D;
  gl_Position.w = 1.0;
}