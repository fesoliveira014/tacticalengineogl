#version 150


uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

in vec4 coord;
out vec4 texcoord;

void main(void) {
	texcoord = coord;
	gl_Position = viewProjectionMatrix * modelMatrix * vec4(coord.xyz, 1);
}