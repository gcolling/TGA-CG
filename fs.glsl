#version 330 core
out vec4 FragColor;

in vec2 textCo;
in vec4 selectedC;
in float selectedO;
uniform sampler2D texture;

void main(){
    vec4 fText = texture2D(texture, textCo);
    FragColor = fText;
}
