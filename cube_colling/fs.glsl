#version 330 core
out vec4 FragColor;

in vec3 vertCo;
in vec2 textCo;
in vec3 normCo;

void main(){    
    FragColor = vec4(textCo, 1.0);
}
