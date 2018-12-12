#version 150
// It was expressed that some drivers required this next line to function properly
precision highp float;

in vec3 forFragColor;
in vec2 texCoord;
in vec3 light;

uniform sampler2D tex;

out vec4 fragColor;

void main() {
    if(forFragColor == vec3(-1, -1, -1)){
        fragColor = texture(tex, texCoord) * vec4(light, 1);
    }
    else{
        fragColor = vec4(forFragColor * light, 1);
    }
  //fragColor = forFragColor;
}
