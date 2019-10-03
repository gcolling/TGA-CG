#version 330 core
out vec4 FragColor;

in vec2 textCo;
in vec4 colorO;
in float selectedO;
uniform sampler2D texture;

void main(){
    vec4 nText = texture2D(texture, textCo);
    FragColor = nText * colorO;
}
