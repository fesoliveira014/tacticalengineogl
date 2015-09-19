#version 150 core

uniform mat4 viewProjectionMatrix;
uniform mat4 modelMatrix;

in vec3 position;
in vec4 colour;
in vec2 texCoords;

out Vertex {
    vec4 colour;
	vec2 texCoords;
} OUT;

void main(void) {
    gl_Position = viewProjectionMatrix * modelMatrix * vec4(position, 1.0);
    OUT.colour  = colour;
	OUT.texCoords = texCoords;
}