#version 150
// It was expressed that some drivers required this next line to function properly
precision highp float;

in vec4 forFragColor;

void main() {
  gl_FragColor = forFragColor;
}
