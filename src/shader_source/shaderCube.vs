#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;

out vec3 fragColor;

// uniform vec3 offset;
// uniform int ori;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 color = vec3(0.66f, 1.0f, 0.0f);

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    fragColor = color;
}