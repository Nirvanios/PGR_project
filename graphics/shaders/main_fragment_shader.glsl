#version 150
// It was expressed that some drivers required this next line to function properly
precision highp float;

in vec4 forFragColor;
out vec4 fragColor;

void main() {
  fragColor = forFragColor;
}
