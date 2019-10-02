#version 330 core
layout (location = 0) in vec3 vp;
layout (location = 1) in vec2 vt;
layout (location = 2) in vec3 vn;

uniform mat4 view, projection, model;
in vec4 selectedColor;
in float selected;
out vec2 textCo;
out vec4 selectedC;
out float selectedO;

void main(){
    textCo = vt;
    selectedO = selected;
    selectedC = selectedColor;
    gl_Position = projection * view * model * vec4(vp, 1.0);
}
