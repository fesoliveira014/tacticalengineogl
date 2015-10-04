#version 150

in vec4 texcoord;

out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = vec4(texcoord.w / 128.0, texcoord.w / 256.0, texcoord.w / 512.0, 1.0);
}