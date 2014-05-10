#version 330 core

in VertexData {
  vec3 color;
} i;

out vec4 o_color;
 
void main(){
  o_color.xyz = i.color;
  o_color.w = 1.0;
}