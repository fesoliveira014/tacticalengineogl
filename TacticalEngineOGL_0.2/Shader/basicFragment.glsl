#version 150 core

uniform sampler2D diffuseTex;

in Vertex {
    vec4 colour;
	vec2 texCoords;
} IN;

out vec4 gl_FragColor;

void main(void) {
    gl_FragColor = texture(diffuseTex, IN.texCoords);
}