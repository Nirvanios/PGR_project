#version 150

in vec3 in_Position;

in vec3 aNormal;
in vec2 aTexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 model;

uniform mat4 mvp;
uniform mat4 translate;
uniform mat4 lightSpaceMatrix;

void main()
{
    gl_Position =  mvp * translate * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);

    vs_out.FragPos = vec3(model * vec4(in_Position, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.TexCoords = aTexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
}