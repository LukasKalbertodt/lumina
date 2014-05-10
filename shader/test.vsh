#version 330 core

layout(location = 0) in vec3 i_pos3D;
layout(location = 1) in vec3 i_color;

out VertexData {
  vec3 color;
} o;

void main() {
  gl_Position.xyz = i_pos3D ;//* color.x;
  gl_Position.w = 1.0;
  o.color = i_color;
}