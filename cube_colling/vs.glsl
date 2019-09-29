#version 330 core
layout (location = 0) in vec3 vp;
layout (location = 1) in vec2 vt;
layout (location = 2) in vec3 vn;

uniform mat4 view, proj, model;
out vec3 vertCo;
out vec2 textCo;
out vec3 normCo;

void main(){
    textCo = vt;
    gl_Position = proj * view * model * vec4(vp, 1.0);
}
