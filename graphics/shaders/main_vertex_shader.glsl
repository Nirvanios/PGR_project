#version 150

/*// in_Position was bound to attribute index 0 and in_Color was bound to attribute index 1
in vec3 in_Position;
in vec4 in_Color;
uniform mat4 translate;
uniform mat4 mvp;
// We output the ex_Color variable to the next shader in the chain
out vec4 ex_Color;

void main(void) {
    // Since we are using flat lines, our input only had two points: x and y.
    // Set the Z coordinate to 0 and W coordinate to 1
    gl_Position = mvp * translate * vec4(in_Position, 1.0);

    // Pass the color on to the fragment shader
    ex_Color = in_Color;
}*/

in vec3 inputPosition;
in vec4 inputColor;
in vec3 inputNormal;

uniform mat4 projection, modelview, normalMat;
uniform mat4 translate;
uniform vec3 lightPos;

out vec4 forFragColor;

const vec3 diffuseColor = vec3(0.2, 0.2, 0.2);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

void main(){
  gl_Position = projection * modelview * vec4(inputPosition, 1.0);

  vec3 ambient = 0.2 * specColor;

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

  forFragColor = inputColor + vec4(lambertian*diffuseColor + specular*specColor + ambient, 1.0);
}
