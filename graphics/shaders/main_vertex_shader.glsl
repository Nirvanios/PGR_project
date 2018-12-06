#version 150

in vec3 inputPosition;
uniform vec3 inputColor;
in vec3 inputNormal;

uniform mat4 projection, modelview, normalMat;
uniform vec3 lightPos;

out vec4 forFragColor;

const vec3 diffuseColor = vec3(0.2, 0.2, 0.2);
const vec3 specColor = vec3(0.4, 0.4, 0.4);

uniform int select;

void main(){
  gl_Position = projection * modelview * vec4(inputPosition, 1.0);

  vec3 ambient = 0.1 * specColor;

  // all following gemetric computations are performed in the
  // camera coordinate system (aka eye coordinates)
  vec3 normal = vec3(normalMat * vec4(inputNormal, 0.0));
  vec4 vertPos4 = modelview * vec4(inputPosition, 1.0);
  vec3 vertPos = vec3(vertPos4) / vertPos4.w;
  vec3 lightDir = normalize(lightPos - vertPos);
  vec3 reflectDir = reflect(-lightDir, normal);
  vec3 viewDir = normalize(-vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);
  float specular = 0.0;

  if(lambertian > 0.0) {
    float specAngle = max(dot(reflectDir, viewDir), 0.0);
    specular = pow(specAngle, 4.0);

    specular *= lambertian;

  }
    if(select == 0){
  forFragColor = vec4(inputColor, 1.0) + vec4(lambertian*diffuseColor + specular*specColor + ambient, 1.0);
  }
  else {
    forFragColor = vec4(inputColor, 1.0);
  }
}
