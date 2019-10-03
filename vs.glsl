#version 330 core
layout (location = 0) in vec3 vp;
layout (location = 1) in vec2 vt;
layout (location = 2) in vec3 vn;

uniform mat4 view, projection, model;
uniform vec4 color;
out vec2 textCo;
out vec4 colorO;

void main(){
    textCo = vt;
    colorO = color;
    gl_Position = projection * view * model * vec4(vp, 1.0);
}
