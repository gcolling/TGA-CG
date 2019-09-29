#version 330 core
out vec4 FragColor;

in vec2 textCo;
uniform sampler2D tex;

void main(){
    vec4 texel0 = texture(tex, textCo);
    if(texel0.a < 0.5){
        discard;
    }
    FragColor = texel0;
}
