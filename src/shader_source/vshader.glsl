#version 330

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// uniform vec3 color = vec3(0.66f, 1.0f, 0.0f);


void main (void) 
{
  gl_Position = projection * view * model * vPosition;
  color = vColor;
}
