#version 150

in vec3 inputPosition;
in vec3 inputNormal;
in vec2 inputTexCoord;

uniform vec3 inputColor;
uniform mat4 projection, modelview;
uniform vec3 lightPos;
uniform vec3 cameraPos;

out vec3 forFragColor;
out vec3 light;
out vec2 texCoord;

const vec3 lightColor = vec3(1, 1, 1);

uniform int select;

void main(){
  gl_Position = projection * modelview * vec4(inputPosition, 1.0);

  float specularStrength = 0.5;

  vec3 ambient = 0.1 * lightColor;
  vec3 norm = normalize(inputNormal);
  vec3 lightDir = normalize(lightPos - inputPosition);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 viewDir = normalize(cameraPos - inputPosition);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColor;

  texCoord = inputTexCoord;
  forFragColor = inputColor;
  if(select == 0){
    //forFragColor = vec4(((ambient + diffuse + specular) * inputColor), 1);
    light = ambient + diffuse + specular;

  }
  else {
    //forFragColor = vec4(inputColor, 1.0);
    light = vec3(1, 1, 1);
  }
}
